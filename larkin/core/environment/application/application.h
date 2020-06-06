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

#pragma once

#include <string>
#include <vector>

namespace app {

class Application {
 private:
    // The localized name of the application
    std::string* _local_name = nullptr;
    // The bundle identifier of the application
    std::string* _bundle_id = nullptr;
    // The process identifier of the application
    pid_t _process_id = -1;

    void init_with_native(void* native_app);

 public:
    explicit Application(pid_t process_id);
    explicit Application(const char* bundle_id);
    ~Application();
    static std::vector<Application*> get_active_applications();

    void activate();
    const char* get_name() const;
    const char* get_bundle_id() const;
    pid_t get_process_id() const;
};

};  // namespace app
