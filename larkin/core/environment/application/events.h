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

namespace app {

// Application process related events.
//   `launched`: application launched for first time
//   `new_instance`: a new instance of the application launched
//   `end_instance`: an instance was closed for the application
//   `terminated`: all instances of the application were closed
// When an application launches launched is run and new_instance
// for each new instance of the launch.
// When an application is terminated end_instance is run for each
// instance being closed before terminated runs.
enum app_event {
    launched,
    new_instance,
    end_instance,
    terminated
};

// Application instance related events.
//   `launched`: application instance launched for first time
//   `hide`: application instance did hide
//   `unhide`: application instance was unhidden
//   `terminated`: application instance was terminated
enum instance_event {
    launched,
    hide,
    unhide,
    terminated
};

};  // namespace app
