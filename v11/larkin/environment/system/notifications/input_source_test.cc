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

#include "googletest/include/gtest/gtest.h"
#include "larkin/environment/system/notifications/input_source.h"
#include "larkin/environment/system/notifications/input_source_mock.h"
#include "larkin/environment/system/notifications/input_source_base.h"
#include "larkin/environment/system/notifications/notification_builder.h"
#include "larkin/environment/system/notifications/notification.h"

using sys::InputSource;
using sys::InputSourceSettings;
using sys::tests::MockInputSource;
using sys::Notification;
using sys::NotificationBuilder;

// Tests that input source's enable method initially match the default input
// source settings value for enabled.
TEST(V11LarkinSysNotificationsInputSourceTest, EnableMatchesDefault) {
    InputSourceSettings settings;
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    EXPECT_EQ(source->IsEnabled(), settings.enabled);
}

// Tests that the enabled switch does not just flip every IsEnabled() call
TEST(V11LarkinSysNotificationsInputSourceTest, EnableDoesNotFlip) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetEnabled(false);
    EXPECT_FALSE(source->IsEnabled());
    source->SetEnabled(false);
    EXPECT_FALSE(source->IsEnabled());
    source->SetEnabled(true);
    EXPECT_TRUE(source->IsEnabled());
    source->SetEnabled(true);
    EXPECT_TRUE(source->IsEnabled());
}

// Tests that changes to the input sources enable method result in the
// source enabling or disabling.
TEST(V11LarkinSysNotificationsInputSourceTest, EnableChangesPropogate) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetEnabled(false);
    EXPECT_FALSE(source->IsEnabled());
    source->SetEnabled(true);
    EXPECT_TRUE(source->IsEnabled());
    source->SetEnabled(false);
    EXPECT_FALSE(source->IsEnabled());
}

// Tests that input source's store memory method initially match the default
// input source settings value for store memory.
TEST(V11LarkinSysNotificationsInputSourceTest, StoreMemoryMatchesDefault) {
    InputSourceSettings settings;
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    EXPECT_EQ(source->IsStoringMemory(), settings.store_memory);
}

// Tests that the store memory switch does not just flip every call
TEST(V11LarkinSysNotificationsInputSourceTest, StoreMemoryDoesNotFlip) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetStoringMemory(false);
    EXPECT_FALSE(source->IsStoringMemory());
    source->SetStoringMemory(false);
    EXPECT_FALSE(source->IsStoringMemory());
    source->SetStoringMemory(true);
    EXPECT_TRUE(source->IsStoringMemory());
    source->SetStoringMemory(true);
    EXPECT_TRUE(source->IsStoringMemory());
}

// Tests that changes to the input sources store memory method result in the
// source enabling or disabling.
TEST(V11LarkinSysNotificationsInputSourceTest, StoreMemoryChangesPropogate) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetStoringMemory(false);
    EXPECT_FALSE(source->IsStoringMemory());
    source->SetStoringMemory(true);
    EXPECT_TRUE(source->IsStoringMemory());
    source->SetStoringMemory(false);
    EXPECT_FALSE(source->IsStoringMemory());
}

// Tests that internal memory system is null when memory is not being stored 
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryWhenNotStoringMemory) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetStoringMemory(false);
    EXPECT_FALSE(source->IsStoringMemory());
    EXPECT_EQ(source->GetMemory(), nullptr);
}

// Tests that internal memory system is null when when not being stored even
// if input source is enabled.
TEST(V11LarkinSysNotificationsInputSourceTest, EnabledWhenNotStoringMemory) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetEnabled(true);
    source->SetStoringMemory(false);
    EXPECT_FALSE(source->IsStoringMemory());
    EXPECT_EQ(source->GetMemory(), nullptr);
}

// Tests that internal memory system is null when when not being stored even
// if input source is disabled.
TEST(V11LarkinSysNotificationsInputSourceTest, DisabledWhenNotStoringMemory) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetEnabled(false);
    source->SetStoringMemory(false);
    EXPECT_FALSE(source->IsStoringMemory());
    EXPECT_EQ(source->GetMemory(), nullptr);
}

// Tests that internal memory system is not null when memory is being stored 
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryWhenStoringMemory) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetStoringMemory(true);
    EXPECT_TRUE(source->IsStoringMemory());
    EXPECT_NE(source->GetMemory(), nullptr);
}

// Tests that internal memory system size is 0 when empty
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryZeroEmptyMemoryStore) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetStoringMemory(true);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that empty internal memory system size is 0 even when disabled.
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryZeroDisabledInput) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetEnabled(false);
    source->SetStoringMemory(true);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that empty internal memory system size is 0 even when enabled.
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryZeroEnabledInput) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    source->SetEnabled(true);
    source->SetStoringMemory(true);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that internal memory system remains null when not storing memory
// even when delivered a notification.
TEST(V11LarkinSysNotificationsInputSourceTest, NoMemoryStoreRemainsEmpty) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder = NotificationBuilder::Create();
    Notification* notification = builder->Build();

    source->SetStoringMemory(false);
    mock_source.CallCallbackMethod(notification);
    EXPECT_EQ(source->GetMemory(), nullptr);
}

// Tests that internal memory system remains empty even when enabled if
// the input source is not enabled.
TEST(V11LarkinSysNotificationsInputSourceTest, DisabledSourceRemainsEmpty) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder = NotificationBuilder::Create();
    Notification* notification = builder->Build();

    source->SetEnabled(false);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that internal memory system has size of 1 if delivered notification
// before memory was enabled and then afterwards.
TEST(V11LarkinSysNotificationsInputSourceTest, FlippedEnableMemoryIsOne) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder_one = NotificationBuilder::Create();
    Notification* notification_one = builder_one->Build();
    NotificationBuilder* builder_two = NotificationBuilder::Create();
    Notification* notification_two = builder_two->Build();

    source->SetEnabled(true);
    source->SetStoringMemory(false);
    mock_source.CallCallbackMethod(notification_one);
    EXPECT_EQ(source->GetMemory(), nullptr);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification_two);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
}

// Tests that internal memory system has size of 1 if delivered notification
// before input source was enabled and then afterwards.
TEST(V11LarkinSysNotificationsInputSourceTest, FlippedEnableSourceIsOne) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder_one = NotificationBuilder::Create();
    Notification* notification_one = builder_one->Build();
    NotificationBuilder* builder_two = NotificationBuilder::Create();
    Notification* notification_two = builder_two->Build();

    source->SetEnabled(false);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification_one);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
    source->SetEnabled(true);
    mock_source.CallCallbackMethod(notification_two);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
}

// Tests that internal memory system does not remain empty when storing memory
// and delivered a notification.
TEST(V11LarkinSysNotificationsInputSourceTest, EnabledNotEmpty) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder = NotificationBuilder::Create();
    Notification* notification = builder->Build();

    source->SetEnabled(true);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
}

// Tests that internal memory system will increase size after receiving
// notifications after being delivered the first notification.
TEST(V11LarkinSysNotificationsInputSourceTest, MemorySizeWillIncrease) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder_one = NotificationBuilder::Create();
    Notification* notification_one = builder_one->Build();
    NotificationBuilder* builder_two = NotificationBuilder::Create();
    Notification* notification_two = builder_two->Build();

    source->SetEnabled(true);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification_one);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
    mock_source.CallCallbackMethod(notification_two);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 2);
}

// Tests that internal memory system is cleared when memory disabled
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryWillClearWhenDisabled) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder = NotificationBuilder::Create();
    Notification* notification = builder->Build();

    source->SetEnabled(true);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
    source->SetStoringMemory(false);
    EXPECT_EQ(source->GetMemory(), nullptr);
    source->SetStoringMemory(true);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that internal memory system is not cleared when input source
// is disabled.
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryExistsForDisabledSource) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder = NotificationBuilder::Create();
    Notification* notification = builder->Build();

    source->SetEnabled(true);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
    source->SetEnabled(false);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
}

// Tests that internal memory system is cleared when ClearMemory is called
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryWillClearFromMethod) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder = NotificationBuilder::Create();
    Notification* notification = builder->Build();

    source->SetEnabled(true);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
    source->ClearMemory();
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that internal memory system is cleared even when input source
// is disabled.
TEST(V11LarkinSysNotificationsInputSourceTest, DisabledSoureceWillClear) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    NotificationBuilder* builder = NotificationBuilder::Create();
    Notification* notification = builder->Build();

    source->SetEnabled(true);
    source->SetStoringMemory(true);
    mock_source.CallCallbackMethod(notification);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 1);
    source->SetEnabled(false);
    source->ClearMemory();
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that ClearMemory does nothing with empty storage.
TEST(V11LarkinSysNotificationsInputSourceTest, ClearMemoryNoActionEmpty) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;

    source->SetEnabled(true);
    source->SetStoringMemory(true);
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
    source->ClearMemory();
    EXPECT_EQ(source->GetMemory()->size(), (std::size_t) 0);
}

// Tests that ClearMemory does nothing even with disabled input source and
// disabled input source storage.
TEST(V11LarkinSysNotificationsInputSourceTest, ClearMemoryNoActionDisabled) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;

    source->SetEnabled(false);
    source->SetStoringMemory(false);
    EXPECT_EQ(source->GetMemory(), nullptr);
    source->ClearMemory();
    EXPECT_EQ(source->GetMemory(), nullptr);
}

// Tests that internal memory system returns correct pointer on instantiation
TEST(V11LarkinSysNotificationsInputSourceTest, MemoryDefaultStoringMemory) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    if (source->IsStoringMemory()) {
        EXPECT_NE(source->GetMemory(), nullptr);
    } else {
        EXPECT_EQ(source->GetMemory(), nullptr);
    }
}

// Tests that input source name for mock type is not base
TEST(V11LarkinSysNotificationsInputSourceTest, NameIsOverridenFromBase) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    EXPECT_NE(source->GetInputSourceName(), sys::kBaseInputSourceName);
    EXPECT_EQ(source->GetInputSourceName(), sys::tests::kMockInputSourceName);
}

// Tests that input source settings struct updates with changes through methods
TEST(V11LarkinSysNotificationsInputSourceTest, SettingsMatchGetterMethods) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    const InputSourceSettings& settings = source->GetSettings();
    EXPECT_EQ(source->IsEnabled(), settings.enabled);
    EXPECT_EQ(source->IsStoringMemory(), settings.store_memory);
    source->SetEnabled(!source->IsEnabled());
    EXPECT_EQ(source->IsEnabled(), settings.enabled);
    source->SetStoringMemory(!source->IsStoringMemory());
    EXPECT_EQ(source->IsStoringMemory(), settings.store_memory);
}

// Tests that empty callback is null
TEST(V11LarkinSysNotificationsInputSourceTest, EmptyCallbackIsNull) {
    MockInputSource mock_source = MockInputSource();
    InputSource* source = &mock_source;
    EXPECT_EQ(source->GetCallback(), nullptr);
}
