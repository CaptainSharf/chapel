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

module ChapelAutoLocalAccess {
  use ChapelLocale;

  proc chpl__staticAutoLocalCheck(accessBase: [], loopDomain) param {
    if chpl__isArrayView(accessBase) then return false;

    if accessBase.domain.type == loopDomain.type {
      return loopDomain.supportsAutoLocalAccess();
    }

    if !defaultRectangularSupportsAutoLocalAccess {
      if !accessBase.domain._value.type.isDefaultRectangular() && 
        loopDomain._value.type.isDefaultRectangular() {
          // there might be something we can do dynamically
          return true;
        }
    }

    return false;
  }

  proc chpl__staticAutoLocalCheck(accessBase, loopDomain) param {
    return false;
  }

  // these type overloads are for degenerate cases where the optimization can
  // break a meaningful error message without these
  proc chpl__staticAutoLocalCheck(type accessBase, type loopDomain) param {
    return false;
  }
  proc chpl__staticAutoLocalCheck(accessBase, type loopDomain) param {
    return false;
  }
  proc chpl__staticAutoLocalCheck(type accessBase, loopDomain) param {
    return false;
  }

  proc chpl__dynamicAutoLocalCheck(accessBase, loopDomain) {
    if chpl__staticAutoLocalCheck(accessBase, loopDomain) {
      // if they're the same domain...
      if accessBase.domain == loopDomain &&
         accessBase.domain._value.dist.dsiEqualDMaps(loopDomain._value.dist) then 
        return true;

      // or at least if they were distributed the same way
      if accessBase.domain.dist == loopDomain.dist then return true;

      // if we are iterating over a rectangular that's:
      // 1. not remote
      // 2. falls within the localSubdomain of the array
      //
      // Be also aware that `subset` call below can be expensive if we are not
      // calling on default rectangular
      if loopDomain._value.type.isDefaultRectangular() {
        if loopDomain.locale == here {
          if loopDomain.isSubset(accessBase.localSubdomain()) {
            return true;
          }
        }
      }
    }

    return false;
  }

  // these type overloads are for degenerate cases where the optimization can
  // break a meaningful error message without these
  proc chpl__dynamicAutoLocalCheck(type accessBase, type loopDomain) {
    return false;
  }
  proc chpl__dynamicAutoLocalCheck(accessBase, type loopDomain) {
    return false;
  }
  proc chpl__dynamicAutoLocalCheck(type accessBase, loopDomain) {
    return false;
  }
}
