/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Mikael Lagerkvist <lagerkvist@gecode.org>
 *     Vincent Barichard <Vincent.Barichard@univ-angers.fr>
 *
 *  Copyright:
 *     Christian Schulte, 2005
 *     Mikael Lagerkvist, 2006
 *     Vincent Barichard, 2012
 *
 *  Last modified:
 *     $Date: 2012-04-06 20:45:10 +0900 (金, 06 4 2012) $ by $Author: schulte $
 *     $Revision: 12716 $
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

namespace Test { namespace Float {

  /*
   * Assignments
   *
   */
  inline
  Assignment::Assignment(int n0, const Gecode::FloatVal& d0)
    : n(n0), d(d0) {}
  inline int
  Assignment::size(void) const {
    return n;
  }
  inline
  Assignment::~Assignment(void) {}

  inline
  CpltAssignment::CpltAssignment(int n, const Gecode::FloatVal& d, Gecode::FloatNum s)
    : Assignment(n,d),
      dsv(new Gecode::FloatNum[static_cast<unsigned int>(n)]),
      step(s) {
    for (int i=n; i--; )
      dsv[i] = d.min();
  }
  inline bool
  CpltAssignment::operator()(void) const {
    return dsv[0] <= d.max();
  }
  inline Gecode::FloatNum
  CpltAssignment::operator[](int i) const {
    assert((i>=0) && (i<n));
    return dsv[i];
  }
  inline
  CpltAssignment::~CpltAssignment(void) {
    delete [] dsv;
  }

  forceinline Gecode::FloatNum
  RandomAssignment::randval(void) {
    using namespace Gecode;
    using namespace Gecode::Float;
    return 
      Round.add_down(
        d.min(),
        Round.mul_down(
          Round.div_down(
            Base::rand(static_cast<unsigned int>(Int::Limits::max)),
            static_cast<FloatNum>(Int::Limits::max)
          ),
          Round.sub_down(d.max(),d.min())
        )
      );
  }

  inline
  RandomAssignment::RandomAssignment(int n, const Gecode::FloatVal& d, int a0)
    : Assignment(n,d), vals(new Gecode::FloatNum[n]), a(a0) {
    for (int i=n; i--; )
      vals[i] = randval();
  }

  inline bool
  RandomAssignment::operator()(void) const {
    return a>0;
  }
  inline Gecode::FloatNum
  RandomAssignment::operator[](int i) const {
    assert((i>=0) && (i<n));
    return vals[i];
  }
  inline
  RandomAssignment::~RandomAssignment(void) {
    delete [] vals;
  }

  /*
   * Tests with float constraints
   *
   */
  inline
  Test::Test(const std::string& s, int a, const Gecode::FloatVal& d, Gecode::FloatNum st,
             bool r)
    : Base("Float::"+s), arity(a), dom(d), step(st), reified(r),
      testsearch(true), testfix(true) {}

  inline
  Test::Test(const std::string& s, int a, Gecode::FloatNum min, Gecode::FloatNum max, Gecode::FloatNum st,
             bool r)
    : Base("Float::"+s), arity(a), dom(min,max), step(st), reified(r),
      testsearch(true), testfix(true) {}

  inline
  std::string
  Test::str(Gecode::ExtensionalPropKind epk) {
    using namespace Gecode;
    switch (epk) {
    case EPK_MEMORY: return "Memory";
    case EPK_SPEED:  return "Speed";
    default: return "Def";
    }
  }

  inline
  std::string
  Test::str(Gecode::FloatRelType frt) {
    using namespace Gecode;
    switch (frt) {
    case FRT_LQ: return "Lq";
    case FRT_GQ: return "Gq";
    case FRT_EQ: return "Eq";
    default: ;
    }
    GECODE_NEVER;
    return "NONE";
  }

  inline
  std::string
  Test::str(Gecode::FloatNum f) {
    std::stringstream s;
    s << f;
    return s.str();
  }

  inline
  std::string
  Test::str(const Gecode::FloatArgs& x) {
    std::string s = "";
    for (int i=0; i<x.size()-1; i++)
      s += str(x[i]) + ",";
    return "[" + s + str(x[x.size()-1]) + "]";
  }

  template<class T>
  inline bool
  Test::cmp(T x, Gecode::FloatRelType r, T y) {
    using namespace Gecode;
    switch (r) {
    case FRT_EQ: return x == y;
    case FRT_LQ: return x <= y;
    case FRT_GQ: return x >= y;
    default: ;
    }
    return false;
  }


  /*
   * Iterators for reification modes
   *
   */

  inline
  ReifyModes::ReifyModes(Gecode::ReifyMode rm)
    : i(0) {
    rms[0]=rm;
  }
  inline
  ReifyModes::ReifyModes(Gecode::ReifyMode rm0, Gecode::ReifyMode rm1)
    : i(1) {
    rms[1]=rm0; rms[0]=rm1;
  }
  inline
  ReifyModes::ReifyModes(void)
    : i(2) {
    using namespace Gecode;
    rms[2]=RM_EQV; rms[1]=RM_IMP; rms[0]=RM_PMI;
  }
  inline bool
  ReifyModes::operator()(void) const {
    return i>=0;
  }
  inline void
  ReifyModes::operator++(void) {
    i--;
  }
  inline Gecode::ReifyMode
  ReifyModes::rm(void) const {
    return rms[i];
  }


  inline
  FloatRelTypes::FloatRelTypes(void)
    : i(sizeof(frts)/sizeof(Gecode::FloatRelType)-1) {}
  inline void
  FloatRelTypes::reset(void) {
    i = sizeof(frts)/sizeof(Gecode::FloatRelType)-1;
  }
  inline bool
  FloatRelTypes::operator()(void) const {
    return i>=0;
  }
  inline void
  FloatRelTypes::operator++(void) {
    i--;
  }
  inline Gecode::FloatRelType
  FloatRelTypes::frt(void) const {
    return frts[i];
  }

}}

// STATISTICS: test-float

