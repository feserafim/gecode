/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Vincent Barichard <Vincent.Barichard@univ-angers.fr>
 *
 *  Copyright:
 *     Vincent Barichard, 2012
 *
 *  Last modified:
 *     $Date: 2012-03-31 00:29:29 +0900 (土, 31 3 2012) $ by $Author: schulte $
 *     $Revision: 12675 $
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

namespace Gecode { namespace Float { namespace Arithmetic {


  /*
   * Bounds consistent square operator
   *
   */

  template<class A, class B>
  forceinline
  Pow<A,B>::Pow(Home home, A x0, B x1, unsigned int n)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,x0,x1), m_n(n) {}

  template<class A, class B>
  ExecStatus
  Pow<A,B>::post(Home home, A x0, B x1, unsigned int n) {
    (void) new (home) Pow<A,B>(home,x0,x1,n);
    return ES_OK;
  }

  template<class A, class B>
  forceinline
  Pow<A,B>::Pow(Space& home, bool share, Pow<A,B>& p)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,share,p), m_n(p.m_n) {}

  template<class A, class B>
  Actor*
  Pow<A,B>::copy(Space& home, bool share) {
    return new (home) Pow<A,B>(home,share,*this);
  }

  template<class A, class B>
  ExecStatus
  Pow<A,B>::propagate(Space& home, const ModEventDelta&) {
    GECODE_ME_CHECK(x1.eq(home,pow(x0.domain(),m_n)));
    if ((m_n % 2) == 0)
    {
      if (x0.min() >= 0)
        GECODE_ME_CHECK(x0.eq(home,nth_root(x1.domain(),m_n)));
      else if (x0.max() <= 0)
        GECODE_ME_CHECK(x0.eq(home,-nth_root(x1.domain(),m_n)));
      else
        GECODE_ME_CHECK(x0.eq(home,
                              hull(
                                  nth_root(x1.domain(),m_n),
                                  -nth_root(x1.domain(),m_n)
                              )
                        ));
    } else
      GECODE_ME_CHECK(x0.eq(home,nth_root(x1.domain(),m_n)));
    return x0.assigned() ? home.ES_SUBSUMED(*this) : ES_FIX;
  }

  /*
   * Bounds consistent square root operator
   *
   */

  template<class A, class B>
  forceinline
  NthRoot<A,B>::NthRoot(Home home, A x0, B x1, unsigned int n)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,x0,x1), m_n(n) {}

  template<class A, class B>
  ExecStatus
  NthRoot<A,B>::post(Home home, A x0, B x1, unsigned int n) {
    (void) new (home) NthRoot<A,B>(home,x0,x1,n);
    return ES_OK;
  }

  template<class A, class B>
  forceinline
  NthRoot<A,B>::NthRoot(Space& home, bool share, NthRoot<A,B>& p)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,share,p), m_n(p.m_n) {}

  template<class A, class B>
  Actor*
  NthRoot<A,B>::copy(Space& home, bool share) {
    return new (home) NthRoot<A,B>(home,share,*this);
  }

  template<class A, class B>
  ExecStatus
  NthRoot<A,B>::propagate(Space& home, const ModEventDelta&) {
    GECODE_ME_CHECK(x1.eq(home,nth_root(x0.domain(),m_n)));
    GECODE_ME_CHECK(x0.eq(home,pow(x1.domain(),m_n)));
    return x0.assigned() ? home.ES_SUBSUMED(*this) : ES_FIX;
  }


}}}

// STATISTICS: float-prop

