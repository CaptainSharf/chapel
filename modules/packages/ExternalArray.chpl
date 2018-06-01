/*
 * Copyright 2004-2018 Cray Inc.
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

// ExternalArray
//
// This module provides an array domain map class that is used to represent
// arrays obtained from external code to Chapel (and thus that we do not own).
//
module ExternalArray {
  use ChapelStandard;

  pragma "use default init"
  class ExternDist: BaseDist {

    proc dsiNewRectangularDom(param rank: int = 1, type idxType = int,
                              param stridable: bool = false, inds) {
      if (rank != 1) {
        halt("external arrays are only allowed a rank of 1 right now");
      }
      if (stridable) {
        halt("external arrays are not allowed to be stridable right now");
      }
      if (!isIntegralType(idxType)) {
        halt("external arrays only allow integral indices");
      }
      if (inds.size != 1) {
        halt("there should only be one set of indices, not multiple dimensions");
      }
      var r = inds(1);
      if (r.low != 0) {
        halt("external arrays always have a lower bound of 0");
      }
      var newdom = new unmanaged ExternDom(idxType,
                                           r.size,
                                           _to_unmanaged(this));
      return newdom;
    }

    proc dsiClone() {
      return this;
    }
  }

  class ExternDom: BaseRectangularDom {
    const size: uint; // We don't need a lower bound, it will always be zero

    const dist;

    proc init(type idxType, size, dist) {
      super.init(1, idxType, false);
      this.size = size: uint;
      this.dist = dist;
    }

    proc dsiBuildArray(type eltType) {
      var arr = new unmanaged ExternArr(eltType,
                                        _to_unmanaged(this),
                                        c_malloc(eltType, this.size),
                                        true);
      return arr;
    }

    proc domRange return 0..#size;

    proc dsiGetIndices() return (domRange,);

    proc dsiSetIndices(x) {
      halt("Can't change the indices of an external array");
    }

    iter these() {
      for i in domRange do
        yield i;
    }

    iter these(param tag: iterKind) where tag == iterKind.standalone {
      forall i in domRange do
        yield i;
    }

    iter these(param tag: iterKind) where tag == iterKind.leader {
      for followThis in domRange {
        yield followThis;
      }
    }

    iter these(param tag: iterKind, followThis)
      where tag == iterKind.follower {
      for i in domRange do
        yield i;
    }

    proc dsiMyDist() {
      return dist;
    }

    proc dsiMember(ind: rank*idxType) {
      if (ind(1) < size && ind(1) >= 0) {
        return true;
      } else {
        return false;
      }
    }

    proc dsiDim(d: int) {
      if (d != rank) {
        halt("domains over external arrays have only one dimension");
      }
      return domRange;
    }

    // Necessary?
    proc dsiDim(param d: int) {
      if (d != rank) {
        halt("domains over external arrays have only one dimension");
      }
      return dsiGetIndices();
    }

    proc dsiAssignDomain(rhs: domain, lhsPrivate: bool) {
      chpl_assignDomainWithGetSetIndices(this, rhs);
    }

    // What about _getActualDom?  dsiDestroyDom?

    // Prolly want the privatization stuff eventually, but I don't need it right
    // now.
  }

  class ExternArr: BaseArr {
    type eltType;

    const dom;
    
    const _ArrInstance: _ddata;

    const _owned: bool;

    proc init(type eltType, const dom, const _ArrInstance, _owned: bool) {
      super.init(_decEltRefCounts = false);
      this.eltType = eltType;
      this.dom = dom;
      this._ArrInstance = _ArrInstance: _ddata(eltType);
      this._owned = _owned;
    }

    proc idxType type return dom.idxType;
    proc rank param return dom.rank;

    // do I want a "isExtern" method on BaseArr?

    //
    // standard iterators
    //

    iter these() ref {
      for elem in chpl__serialViewIter(this, privDom) do
        yield elem;
    }

    iter these(param tag: iterKind) ref
      where tag == iterKind.standalone && !localeModelHasSublocales &&
           __primitive("method call resolves", privDom, "these", tag) {
      forall i in privDom do yield dsiAccess(i);
    }

    iter these(param tag: iterKind) where tag == iterKind.leader {
      for followThis in privDom.these(tag) do {
        yield followThis;
      }
    }

    iter these(param tag: iterKind, followThis) ref
      where tag == iterKind.follower {
      for i in privDom.these(tag, followThis) {
        yield dsiAccess[i];
      }
    }

    proc dsiSerialWrite(f) {
      chpl_serialReadWriteRectangular(f, this, privDom);
    }

    proc dsiSerialRead(f) {
      chpl_serialReadWriteRectangular(f, this, privDom);
    }

    // Probably want dsiDisplayRepresentation? (see ArrayViewSlice.chpl:153-161)

    inline proc dsiAccess(i: idxType ...rank) ref {
      return dsiAccess(i);
    }

    inline proc dsiAccess(i: idxType ...rank)
      where shouldReturnRvalueByValue(eltType) {
      return dsiAccess(i);
    }

    inline proc dsiAccess(i: idxType ...rank) const ref
      where shouldReturnRvalueByConstRef(eltType) {
      return dsiAccess(i);
    }

    inline proc dsiAccess(i) ref {
      checkBounds(i);
      return _ArrInstance(i(1));
    }

    inline proc dsiAccess(i)
      where shouldReturnRvalueByValue(eltType) {
      checkBounds(i);
      return _ArrInstance(i(1));
    }

    inline proc dsiAccess(i) const ref
      where shouldReturnRvalueByConstRef(eltType)  {
      checkBounds(i);
      return _ArrInstance(i(1));
    }

    inline proc checkBounds(i) {
      if boundsChecking then
        if !dom.dsiMember(i) {
          halt("array index out of bounds: " + _stringify_tuple(i));
        }
    }
    // arr inline proc?

    inline proc dsiGetBaseDom() {
      return dom;
    }

    // _getActualArray - useful for returning the array?  Or a dangerous insight
    // into the implementation?

    // PUNT FOR NOW, WILL NEED EVENTUALLY:
    // Do I want the locality-oriented queries? (see
    // ArrayViewSlice.chpl:225-230)
    // What about the privatization?
    // doiCanBulkTransferRankChange? doiBulkTransferFromKnown?
    // doiBulkTransferToKnown?

    proc dsiDestroyArr() {
      if (_owned) {
        _ddata_free(_ArrInstance, dom.size);
      }
    }

    inline proc privDom {
      /*if _isPrivatized(dom) {
        return chpl_getPrivatizedCopy(dom.type, _DomPid);
        } else {*/
        return dom;
        //}
    }

    // proc dsiReallocate(d: domain) is not supported, so don't override.
    // proc _resize(length: int, old_map) is not supported, don't override.
  }

  // Creates an instance of our new array type
  pragma "no copy return"
  proc makeArrayFromPtr(value: c_ptr, size: uint) {
    var dist = new unmanaged ExternDist();
    var dom = dist.dsiNewRectangularDom(idxType=int, inds=(0..#size,));
    dom._free_when_no_arrs = true;
    var arr = new unmanaged ExternArr(value.eltType,
                                      dom,
                                      value,
                                      false);
    dom.add_arr(arr, locking = false);
    return _newArray(arr);
  }
}
