/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#define __unused__ (void)

#define new_space(obj) reinterpret_cast<obj*>(::operator new (sizeof(obj)))

#define print(text) fprintf(stderr, "%s\n", text)
#define print_string(text) fprintf(stderr, "%s\n", text.c_str())

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // Environment specific platform is windows
    #define PLATFORM_WINDOWS true
#elif __APPLE__
    // Environment specific platform is mac os
    #define PLATFORM_MAC true
#elif __linux__
    // Environment specific platform is mac os
    #define PLATFORM_LINUX true
#endif
