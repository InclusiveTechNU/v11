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

using sys::InputSource;
using sys::InputSourceSettings;
using sys::tests::MockInputSource;

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
