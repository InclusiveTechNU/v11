{
  "targets": [
    {
      "target_name": "larkin",
      'include_dirs': [
          '.',
          "<!@(node -p \"require('get-uv-event-loop-napi-h').include\")",
      ],
      'dependencies': [
        'libcore-a11y',
        'libcore',
      ],
      "sources": [
        # Main Binding File
        "client/node/binding.cc",
        "client/node/utils.h",
        "client/node/utils.cc",

        # Interactions
        "client/node/interaction.h",
        "client/node/interaction.cc",
        "client/node/sound_utils.h",
        "client/node/sound_utils.cc",

        # Environment
        "client/node/environment.h",
        "client/node/environment.cc",

        # Accessibility
        "client/node/accessibility.h",
        "client/node/accessibility.cc"
      ],
      "cflags": [
        "-std=c++17",
        "-stdlib=libc++",
        "-ObjC++",
      ]
    },

    {
      "target_name": "libcore-a11y",
      'type': 'static_library',
      'include_dirs': [
          'core/accessibility',
      ],
      'dependencies': [
        'libcore',
      ],
       "sources": [
        ### CORE/ACCESSIBILITY ###
        "core/accessibility/accessibility_tree.h",
        "core/accessibility/accessibility_tree.cc",
        "core/accessibility/accessibility_tree_mac.mm",
        "core/accessibility/accessibility_element.h",
        "core/accessibility/accessibility_element.cc",
        "core/accessibility/accessibility_element_mac.mm",
        "core/accessibility/accessibility.h",
        "core/accessibility/accessibility_mac.mm",
        "core/accessibility/accessibility_window.h",
        "core/accessibility/accessibility_window.cc",
        "core/accessibility/accessibility_window_mac.mm",
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          'core/accessibility',
        ],
      },
      'link_settings': {
        'libraries': [
          '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
          '$(SDKROOT)/System/Library/Frameworks/AppKit.framework',
        ],
      },
      "cflags": [
        "-std=c++17",
        "-stdlib=libc++",
        "-ObjC++"
      ]
    },

    {
      "target_name": "libcore",
      'type': 'static_library',
      'include_dirs': [
          'core/',
      ],
      "sources": [
        ### CORE/ENVIRONMENT ###
        "core/environment/system/system.h",
        "core/environment/system/system_bridge.h",
        "core/environment/system/system_initializer.h",
        "core/environment/system/notifications/listener.h",
        "core/environment/system/notifications/notification.h",
        "core/environment/system/notifications/notification_utils.h",
        "core/environment/system/notifications/notification_utils_bridge.h",
        "core/environment/system/notifications/manager_type.h",
        "core/environment/system/platform/platform_info.h",
        "core/environment/system/platform/get_platform.h",
        "core/environment/system/notifications/notification_manager.h",
        "core/environment/system/platform/platform.h",
        "core/environment/system/notifications/notification_manager_bridge.h",
        "core/environment/system/notifications/notification.cc",
        "core/environment/system/notifications/notification_utils.cc",
        "core/environment/system/notifications/notification_utils_bridge_mac.mm",
        "core/environment/system/notifications/notification_manager.cc",
        "core/environment/system/platform/platform.cc",
        "core/environment/system/platform/get_platform_mac.mm",
        "core/environment/system/notifications/notification_manager_bridge_mac.mm",
        "core/environment/system/system_delegate_mac.mm",
        "core/environment/system/system_bridge_mac.mm",
        "core/environment/system/system_delegate_mac.h",
        "core/environment/system/system.cc",
        "core/environment/application/application.h",
        "core/environment/application/application.cc",
        "core/environment/application/application_mac.mm",
        "core/environment/application/application_observer_bridge.h",
        "core/environment/application/application_observer_bridge_mac.mm",
        "core/environment/application/application_observer.h",
        "core/environment/application/application_observer.cc",

        ### CORE/UTILS ###
        "core/utils/string.cc",
        "core/utils/definitions.h",
        "core/utils/error.h",
        "core/utils/string.h",
        "core/utils/run_main_mac.mm",
        "core/utils/run_main.h",

        ### CORE/INTERACTION ###
        "core/interaction/sound/sound_manager.cc",
        "core/interaction/sound/text2speech/text2speech_synthesizer.cc",
        "core/interaction/sound/text2speech/text2speech_synthesizer_bridge_mac.mm",
        "core/interaction/sound/text2speech/voice_bridge_mac.mm",
        "core/interaction/sound/text2speech/voice.cc",

        "core/interaction/keyboard/keycode_converter_mac.mm",
        "core/interaction/keyboard/keyboard_simulator_bridge_mac.mm",
        "core/interaction/keyboard/keyboard_simulator.cc",
        "core/interaction/keyboard/keyboard_event.cc",
        "core/interaction/keyboard/keyboard_listener_bridge_mac.mm",
        "core/interaction/keyboard/keyboard_listener.cc"
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          'core/',
        ],
      },
      'link_settings': {
        'libraries': [
          '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
          '$(SDKROOT)/System/Library/Frameworks/AppKit.framework',
        ],
      },
      "cflags": [
        "-std=c++17",
        "-stdlib=libc++",
        "-ObjC++"
      ]
    }
  ]
}