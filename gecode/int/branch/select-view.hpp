/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2002
 *
 *  Last modified:
 *     $Date: 2012-03-06 22:02:26 +0900 (火, 06 3 2012) $ by $Author: schulte $
 *     $Revision: 12548 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

namespace Gecode { namespace Int { namespace Branch {

  // Select variable with smallest min
  forceinline
  ByMinMin::ByMinMin(void) : min(0) {}
  forceinline
  ByMinMin::ByMinMin(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), min(0) {}
  forceinline ViewSelStatus
  ByMinMin::init(Space&, View x, int) {
    min = x.min();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByMinMin::select(Space&, View x, int) {
    if (x.min() < min) {
      min = x.min(); return VSS_BETTER;
    } else if (x.min() > min) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with largest min
  forceinline
  ByMinMax::ByMinMax(void) : min(0) {}
  forceinline
  ByMinMax::ByMinMax(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), min(0) {}
  forceinline ViewSelStatus
  ByMinMax::init(Space&, View x, int) {
    min = x.min();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByMinMax::select(Space&, View x, int) {
    if (x.min() > min) {
      min = x.min(); return VSS_BETTER;
    } else if (x.min() < min) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with smallest max
  forceinline
  ByMaxMin::ByMaxMin(void) : max(0) {}
  forceinline
  ByMaxMin::ByMaxMin(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), max(0) {}
  forceinline ViewSelStatus
  ByMaxMin::init(Space&, View x, int) {
    max = x.max();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByMaxMin::select(Space&, View x, int) {
    if (x.max() < max) {
      max = x.max(); return VSS_BETTER;
    } else if (x.max() > max) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with largest max
  forceinline
  ByMaxMax::ByMaxMax(void) : max(0) {}
  forceinline
  ByMaxMax::ByMaxMax(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), max(0) {}
  forceinline ViewSelStatus
  ByMaxMax::init(Space&, View x, int) {
    max = x.max();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByMaxMax::select(Space&, View x, int) {
    if (x.max() > max) {
      max = x.max(); return VSS_BETTER;
    } else if (x.max() < max) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with smallest size
  forceinline
  BySizeMin::BySizeMin(void) : size(0U) {}
  forceinline
  BySizeMin::BySizeMin(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), size(0U) {}
  forceinline ViewSelStatus
  BySizeMin::init(Space&, View x, int) {
    size = x.size();
    return (size == 2) ? VSS_BEST : VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeMin::select(Space&, View x, int) {
    if (x.size() < size) {
      size = x.size();
      return (size == 2) ? VSS_BEST : VSS_BETTER;
    } else if (x.size() > size) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with largest size
  forceinline
  BySizeMax::BySizeMax(void) : size(0U) {}
  forceinline
  BySizeMax::BySizeMax(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), size(0U) {}
  forceinline ViewSelStatus
  BySizeMax::init(Space&, View x, int) {
    size = x.size();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeMax::select(Space&, View x, int) {
    if (x.size() > size) {
      size = x.size();
      return VSS_BETTER;
    } else if (x.size() < size) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with smallest size/degree
  forceinline
  BySizeDegreeMin::BySizeDegreeMin(void) : sizedegree(0) {}
  forceinline
  BySizeDegreeMin::BySizeDegreeMin(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), sizedegree(0) {}
  forceinline ViewSelStatus
  BySizeDegreeMin::init(Space&, View x, int) {
    sizedegree =
      static_cast<double>(x.size())/static_cast<double>(x.degree());
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeDegreeMin::select(Space&, View x, int) {
    double sd =
      static_cast<double>(x.size())/static_cast<double>(x.degree());
    if (sd < sizedegree) {
      sizedegree = sd; return VSS_BETTER;
    } else if (sd > sizedegree) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with largest size/degree
  forceinline
  BySizeDegreeMax::BySizeDegreeMax(void) : sizedegree(0) {}
  forceinline
  BySizeDegreeMax::BySizeDegreeMax(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), sizedegree(0) {}
  forceinline ViewSelStatus
  BySizeDegreeMax::init(Space&, View x, int) {
    sizedegree =
      static_cast<double>(x.size())/static_cast<double>(x.degree());
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeDegreeMax::select(Space&, View x, int) {
    double sd =
      static_cast<double>(x.size())/static_cast<double>(x.degree());
    if (sd > sizedegree) {
      sizedegree = sd; return VSS_BETTER;
    } else if (sd < sizedegree) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with smallest size/afc
  forceinline
  BySizeAfcMin::BySizeAfcMin(void) : sizeafc(0) {}
  forceinline
  BySizeAfcMin::BySizeAfcMin(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), sizeafc(0) {}
  forceinline ViewSelStatus
  BySizeAfcMin::init(Space&, View x, int) {
    sizeafc = static_cast<double>(x.size())/x.afc();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeAfcMin::select(Space&, View x, int) {
    double sa = static_cast<double>(x.size())/x.afc();
    if (sa < sizeafc) {
      sizeafc = sa; return VSS_BETTER;
    } else if (sa > sizeafc) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with largest size/afc
  forceinline
  BySizeAfcMax::BySizeAfcMax(void) : sizeafc(0) {}
  forceinline
  BySizeAfcMax::BySizeAfcMax(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), sizeafc(0) {}
  forceinline ViewSelStatus
  BySizeAfcMax::init(Space&, View x, int) {
    sizeafc = static_cast<double>(x.size())/x.afc();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeAfcMax::select(Space&, View x, int) {
    double sa = static_cast<double>(x.size())/x.afc();
    if (sa > sizeafc) {
      sizeafc = sa; return VSS_BETTER;
    } else if (sa < sizeafc) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with smallest size/activity
  forceinline
  BySizeActivityMin::BySizeActivityMin(void) : sizeact(0.0) {}
  forceinline
  BySizeActivityMin::BySizeActivityMin(Space& home,
                                       const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), activity(vbo.activity), sizeact(0.0) {
    if (!activity.initialized())
      throw MissingActivity("BySizeActivityMin (INT_VAR_SIZE_ACTIVITY_MIN)");
  }
  forceinline ViewSelStatus
  BySizeActivityMin::init(Space&, View x, int i) {
    sizeact = static_cast<double>(x.size())/activity[i];
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeActivityMin::select(Space&, View x, int i) {
    double sa = static_cast<double>(x.size())/activity[i];
    if (sa < sizeact) {
      sizeact = sa;
      return VSS_BETTER;
    } else if (sa > sizeact) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }
  forceinline void
  BySizeActivityMin::update(Space& home, bool share, BySizeActivityMin& vs) {
    activity.update(home, share, vs.activity);
  }
  forceinline bool
  BySizeActivityMin::notice(void) const {
    return true;
  }
  forceinline void
  BySizeActivityMin::dispose(Space&) {
    activity.~Activity();
  }

  // Select variable with largest size/activity
  forceinline
  BySizeActivityMax::BySizeActivityMax(void) : sizeact(0.0) {}
  forceinline
  BySizeActivityMax::BySizeActivityMax(Space& home,
                                       const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), activity(vbo.activity), sizeact(0.0) {
    if (!activity.initialized())
      throw MissingActivity("BySizeActivityMax (INT_VAR_SIZE_ACTIVITY_MAX)");
  }
  forceinline ViewSelStatus
  BySizeActivityMax::init(Space&, View x, int i) {
    sizeact = static_cast<double>(x.size())/activity[i];
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  BySizeActivityMax::select(Space&, View x, int i) {
    double sa = static_cast<double>(x.size())/activity[i];
    if (sa > sizeact) {
      sizeact = sa;
      return VSS_BETTER;
    } else if (sa < sizeact) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }
  forceinline void
  BySizeActivityMax::update(Space& home, bool share, BySizeActivityMax& vs) {
    activity.update(home, share, vs.activity);
  }
  forceinline bool
  BySizeActivityMax::notice(void) const {
    return true;
  }
  forceinline void
  BySizeActivityMax::dispose(Space&) {
    activity.~Activity();
  }

  // Select variable with smallest min-regret
  forceinline
  ByRegretMinMin::ByRegretMinMin(void) : regret(0U) {}
  forceinline
  ByRegretMinMin::ByRegretMinMin(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), regret(0U) {}
  forceinline ViewSelStatus
  ByRegretMinMin::init(Space&, View x, int) {
    regret = x.regret_min();
    return (regret == 1) ? VSS_BEST : VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByRegretMinMin::select(Space&, View x, int) {
    if (x.regret_min() < regret) {
      regret = x.regret_min();
      return (regret == 1) ? VSS_BEST : VSS_BETTER;
    } else if (x.regret_min() > regret) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with largest min-regret
  forceinline
  ByRegretMinMax::ByRegretMinMax(void) : regret(0U) {}
  forceinline
  ByRegretMinMax::ByRegretMinMax(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), regret(0U) {}
  forceinline ViewSelStatus
  ByRegretMinMax::init(Space&, View x, int) {
    regret = x.regret_min();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByRegretMinMax::select(Space&, View x, int) {
    if (x.regret_min() > regret) {
      regret = x.regret_min();
      return VSS_BETTER;
    } else if (x.regret_min() < regret) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with smallest max-regret
  forceinline
  ByRegretMaxMin::ByRegretMaxMin(void) : regret(0U) {}
  forceinline
  ByRegretMaxMin::ByRegretMaxMin(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), regret(0U) {}
  forceinline ViewSelStatus
  ByRegretMaxMin::init(Space&, View x, int) {
    regret = x.regret_max();
    return (regret == 1) ? VSS_BEST : VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByRegretMaxMin::select(Space&, View x, int) {
    if (x.regret_max() < regret) {
      regret = x.regret_max();
      return (regret == 1) ? VSS_BEST : VSS_BETTER;
    } else if (x.regret_max() > regret) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

  // Select variable with largest max-regret
  forceinline
  ByRegretMaxMax::ByRegretMaxMax(void) : regret(0U) {}
  forceinline
  ByRegretMaxMax::ByRegretMaxMax(Space& home, const VarBranchOptions& vbo)
    : ViewSelBase<IntView>(home,vbo), regret(0U) {}
  forceinline ViewSelStatus
  ByRegretMaxMax::init(Space&, View x, int) {
    regret = x.regret_max();
    return VSS_BETTER;
  }
  forceinline ViewSelStatus
  ByRegretMaxMax::select(Space&, View x, int) {
    if (x.regret_max() > regret) {
      regret = x.regret_max();
      return VSS_BETTER;
    } else if (x.regret_max() < regret) {
      return VSS_WORSE;
    } else {
      return VSS_TIE;
    }
  }

}}}

// STATISTICS: int-branch
