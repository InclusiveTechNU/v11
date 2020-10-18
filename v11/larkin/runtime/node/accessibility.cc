/*
 * Copyright 2020 Northwestern Inclusive Technology Lab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <vector>
#include "larkin/runtime/node/accessibility.h"
#include "larkin/runtime/node/utils.h"
#include "larkin/accessibility/accessibility_tree.h"
#include "larkin/accessibility/accessibility_element.h"
#include "larkin/environment/application/application.h"
#include "larkin/environment/system/notifications/notification.h"

using app::Application;
using utils::string_from_value;
using utils::element_to_object;
using utils::window_to_object;
using a11y::AccessibilityWindow;
using a11y::AccessibilityTree;
using a11y::AccessibilityElement;
using sys::NotificationType;

// TODO(tommymchugh): This should be moved somewhere else
#define NOTIF_TYPE_APPLICATION_DID_CHANGE_MAIN_WINDOW "unknown"
#define NOTIF_TYPE_APPLICATION_DID_CHANGE_FOCUSED_WINDOW "unknown"
#define NOTIF_TYPE_APPLICATION_DID_CHANGE_FOCUSED_ELEMENT "unknown"
#define NOTIF_TYPE_APPLICATION_DID_CREATE_WINDOW "unknown"
#define NOTIF_TYPE_APPLICATION_DID_REMOVE_ELEMENT "unknown"

// TODO(tommymchugh): Check for element type for some of these
#define NOTIF_TYPE_WINDOW_ELEMENT_DID_FINISH_MOVE "finishmove"
#define NOTIF_TYPE_WINDOW_ELEMENT_DID_FINISH_RESIZE "finishresize"
#define NOTIF_TYPE_WINDOW_ELEMENT_DID_MINIMIZE "minimize"
#define NOTIF_TYPE_WINDOW_ELEMENT_DID_DEMINIMIZE "deminimize"
#define NOTIF_TYPE_UI_ELEMENT_DID_RESIZE "resize"
#define NOTIF_TYPE_UI_ELEMENT_DID_MOVE "move"
#define NOTIF_TYPE_UI_ELEMENT_DID_CHANGE_TITLE "title"
#define NOTIF_TYPE_UI_ELEMENT_DID_CHANGE_VALUE "value"
#define NOTIF_TYPE_UI_ELEMENT_REMOVED "remove"

namespace a11y {

/*NotificationType convert_string_to_NotificationType(std::string type_str) {
    if (type_str == NOTIF_TYPE_APPLICATION_DID_CHANGE_MAIN_WINDOW) {
        return NotificationType::APPLICATION_DID_CHANGE_MAIN_WINDOW;
    } else if (type_str == NOTIF_TYPE_APPLICATION_DID_CHANGE_FOCUSED_WINDOW) {
        return NotificationType::APPLICATION_DID_CHANGE_FOCUSED_WINDOW;
    } else if (type_str == NOTIF_TYPE_APPLICATION_DID_CHANGE_FOCUSED_ELEMENT) {
        return NotificationType::APPLICATION_DID_CREATE_UI_ELEMENT;
    } else if (type_str == NOTIF_TYPE_APPLICATION_DID_CREATE_WINDOW) {
        return NotificationType::APPLICATION_DID_CREATE_WINDOW;
    } else if (type_str == NOTIF_TYPE_APPLICATION_DID_REMOVE_ELEMENT) {
        return NotificationType::APPLICATION_DID_REMOVE_ELEMENT;
    } else {
        return NotificationType::kUnknownNotification;
    }
}*/

NotificationType convert_string_to_notification_type(std::string type_str) {
    if (type_str == NOTIF_TYPE_WINDOW_ELEMENT_DID_FINISH_MOVE) {
        return NotificationType::kWindowDidFinishMove;
    } else if (type_str == NOTIF_TYPE_WINDOW_ELEMENT_DID_FINISH_RESIZE) {
        return NotificationType::kWindowDidFinishResize;
    } else if (type_str == NOTIF_TYPE_WINDOW_ELEMENT_DID_MINIMIZE) {
        return NotificationType::kWindowDidMinimize;
    } else if (type_str == NOTIF_TYPE_WINDOW_ELEMENT_DID_DEMINIMIZE) {
        return NotificationType::kWindowDidDeminimize;
    } else if (type_str == NOTIF_TYPE_UI_ELEMENT_DID_RESIZE) {
        return NotificationType::kUIElementDidResize;
    } else if (type_str == NOTIF_TYPE_UI_ELEMENT_DID_MOVE) {
        return NotificationType::kUIElementDidMove;
    } else if (type_str == NOTIF_TYPE_UI_ELEMENT_DID_CHANGE_TITLE) {
        return NotificationType::kUIElementDidChangeTitle;
    } else if (type_str == NOTIF_TYPE_UI_ELEMENT_DID_CHANGE_VALUE) {
        return NotificationType::kUIElementDidChangeValue;
    } else if (type_str == NOTIF_TYPE_UI_ELEMENT_REMOVED) {
        return NotificationType::kUIElementDidRemove;
    } else {
        return NotificationType::kUnknownNotification;
    }
}

void windows(napi_env env, napi_value exports) {
    napi_value get_windows;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        napi_value windows_array;
        a_ok(napi_create_array(env, &windows_array));

        size_t args_count = 1;
        napi_value args[1];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value process_id_val = args[0];
        pid_t process_id;
        a_ok(napi_get_value_int32(env, process_id_val, &process_id));

        // TODO(tommymchugh): Move to an application variable in raw JS instead
        // of generating one continuously in client
        //TODO(tommymchugh): Handle memory management
        Application* app = new Application(process_id);
        AccessibilityTree* app_tree = new AccessibilityTree(app);
        std::vector<AccessibilityWindow*> windows = app_tree->get_windows();

        for (std::size_t i = 0; i < windows.size(); i++) {
            AccessibilityWindow* window = windows[i];
            napi_value window_object;
            window_to_object(env, window, &window_object);
            a_ok(napi_set_element(env, windows_array, i, window_object));
        }
        return windows_array;
    }, nullptr, &get_windows));

    a_ok(napi_set_named_property(env,
                                 exports,
                                 "getWindows",
                                 get_windows));
}

void listeners(napi_env env, napi_value exports) {
    napi_value add_listener;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        size_t args_count = 3;
        napi_value args[3];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value native_wrapper = args[0];
        void* native_wrapper_ptr = nullptr;
        a_ok(napi_unwrap(env, native_wrapper, &native_wrapper_ptr));
        AccessibilityElement* element =
            reinterpret_cast<AccessibilityElement*>(native_wrapper_ptr);

        napi_value listener_type_object = args[1];
        const char* listener_type_ptr = string_from_value(env, listener_type_object);
        if (!listener_type_ptr) {
            // TODO(tommymchugh): Handle failed string
            return nullptr;
        }
        std::string listener_type_str = std::string(listener_type_ptr);
        NotificationType listener_type =
            convert_string_to_notification_type(listener_type_str);

        napi_value listener_callback_object = args[2];
        napi_threadsafe_function listener_callback;
        napi_value res_name;
        a_ok(napi_create_string_utf8(env, "resource", NAPI_AUTO_LENGTH, &res_name));
        a_ok(napi_create_threadsafe_function(env, listener_callback_object,
                                                 nullptr, res_name,
                                                 0, 2,
                                                 nullptr, nullptr, nullptr,
                                                 nullptr,
                                                 &listener_callback));
        element->add_notification_listener(listener_type, new std::function<void()>([listener_callback]() {
            napi_acquire_threadsafe_function(listener_callback);
            napi_call_threadsafe_function(listener_callback,
                                            nullptr,
                                            napi_tsfn_blocking);
        }));
        delete listener_type_ptr;
        return nullptr;
    }, nullptr, &add_listener));

    a_ok(napi_set_named_property(env,
                                 exports,
                                 "addEventListener",
                                 add_listener));
}

void children(napi_env env, napi_value exports) {
    napi_value get_children;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        napi_value children_array;
        a_ok(napi_create_array(env, &children_array));

        size_t args_count = 1;
        napi_value args[1];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value native_wrapper = args[0];
        void* native_wrapper_ptr = nullptr;
        a_ok(napi_unwrap(env, native_wrapper, &native_wrapper_ptr));
        AccessibilityWindow* native_window =
            reinterpret_cast<AccessibilityWindow*>(native_wrapper_ptr);

        std::vector<AccessibilityElement*> children = native_window->
                                                      get_children();

        for (std::size_t i = 0; i < children.size(); i++) {
            AccessibilityElement* child = children[i];
            napi_value child_object;
            element_to_object(env, child, &child_object);
            a_ok(napi_set_element(env, children_array, i, child_object));
        }
        return children_array;
    }, nullptr, &get_children));
    a_ok(napi_set_named_property(env,
                                 exports,
                                 "getChildren",
                                 get_children));
}

void values(napi_env env, napi_value exports) {
    napi_value set_value;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        size_t args_count = 2;
        napi_value args[2];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value native_wrapper = args[0];
        void* native_wrapper_ptr = nullptr;
        a_ok(napi_unwrap(env, native_wrapper, &native_wrapper_ptr));
        AccessibilityElement* native_window =
            reinterpret_cast<AccessibilityElement*>(native_wrapper_ptr);

        napi_value text_value = args[1];
        char* text = string_from_value(env, text_value);
        native_window->set_value(text);
        delete text;
        return nullptr;
    }, nullptr, &set_value));
    a_ok(napi_set_named_property(env,
                                 exports,
                                 "setValue",
                                 set_value));
}

void actions(napi_env env, napi_value exports) {
    napi_value get_actions;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        napi_value windows_array;
        a_ok(napi_create_array(env, &windows_array));

        size_t args_count = 1;
        napi_value args[1];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value native_wrapper = args[0];
        void* native_wrapper_ptr = nullptr;
        a_ok(napi_unwrap(env, native_wrapper, &native_wrapper_ptr));
        AccessibilityElement* element = reinterpret_cast<AccessibilityElement*>(native_wrapper_ptr);
        std::vector<std::string> actions = element->get_actions();

        for (std::size_t i = 0; i < actions.size(); i++) {
            std::string& action = actions[i];
            napi_value action_object;
            a_ok(napi_create_string_utf8(env,
                                     action.c_str(),
                                     NAPI_AUTO_LENGTH,
                                     &action_object));
            a_ok(napi_set_element(env, windows_array, i, action_object));
        }
        return windows_array;
    }, nullptr, &get_actions));

    a_ok(napi_set_named_property(env,
                                 exports,
                                 "getActions",
                                 get_actions));

    napi_value perform_action;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        size_t args_count = 2;
        napi_value args[2];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value native_wrapper = args[0];
        void* native_wrapper_ptr = nullptr;
        a_ok(napi_unwrap(env, native_wrapper, &native_wrapper_ptr));
        AccessibilityElement* element = reinterpret_cast<AccessibilityElement*>(native_wrapper_ptr);

        napi_value text_value = args[1];
        char* text = string_from_value(env, text_value);
        element->perform_action(text);
        delete text;
        return nullptr;
    }, nullptr, &perform_action));
    a_ok(napi_set_named_property(env,
                                 exports,
                                 "performAction",
                                 perform_action));
}

// Initialize all variables and functions
void init(napi_env env, napi_value exports, System* sys_ptr) {
    napi_value accessibility_object;
    a_ok(napi_create_object(env, &accessibility_object));

    windows(env, accessibility_object);
    children(env, accessibility_object);
    values(env, accessibility_object);
    actions(env, accessibility_object);
    listeners(env, accessibility_object);

    a_ok(napi_set_named_property(env,
                                exports,
                                "accessibility",
                                accessibility_object));
}

}  // namespace a11y
