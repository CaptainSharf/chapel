/*
 * Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright 2004-2019 Cray Inc.
 * Other additional copyright holders may be indicated within.
 * 
 * The entirety of this work is licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 * 
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// This file is used in --llvm compiles to compile the header
// declarations for the Chapel runtime into an LLVM module.

#ifdef __cplusplus
extern "C" {
// Use extern "C" block to avoid name mangling for the
// runtime which is really C.
// TODO: Does this mess up CHPL_REGEXP=re2 support?
//       If so, move the extern "C" into individual headers.
#endif

#include "stdchpl.h"

#include "chpl-gen-includes.h"

#ifdef __cplusplus
}
#endif
