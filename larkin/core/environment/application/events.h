/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
