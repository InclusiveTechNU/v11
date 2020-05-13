/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <node_api.h>
#include "interaction.h"

namespace larkin {

napi_value init(napi_env env, napi_value exports) {
  interaction::init(env, exports);
  return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace larkin
