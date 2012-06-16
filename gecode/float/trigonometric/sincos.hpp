/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Vincent Barichard <Vincent.Barichard@univ-angers.fr>
 *
 *  Copyright:
 *     Vincent Barichard, 2012
 *
 *  Last modified:
 *     $Date: 2012-04-11 13:59:58 +0900 (水, 11 4 2012) $ by $Author: tack $
 *     $Revision: 12731 $
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

namespace Gecode { namespace Float { namespace Trigonometric {


  /*
   * ASin projection function
   *
   */
  template<class V>
  void aSinProject(const V& aSinIv, FloatVal& iv) {
#define I0__PI_2I    FloatVal(0,pi_half_upper())
#define IPI_2__PII   FloatVal(pi_half_lower(),pi_upper())
#define IPI__3PI_2I  FloatVal(pi_lower(),3*pi_half_upper())
#define I3PI_2__2PII FloatVal(3*pi_half_lower(),pi_twice_upper())
#define POS(X) ((I0__PI_2I.in(X))?0: (IPI_2__PII.in(X))?1: (IPI__3PI_2I.in(X))?2: 3 )
#define CASE(X,Y) case ((X << 2) | Y) :
#define CASE_LABEL(X,Y) case ((X << 2) | Y) : CASE_ ## X ## _ ## Y :
#define SHIFTN_UP(N,X) Round.add_up(Round.mul_up(N,pi_twice_upper()),X)
#define SHIFTN_DOWN(N,X) Round.add_down(Round.mul_down(N,pi_twice_lower()),X)
#define GROWING(I) Round.sin_down(iv.min()) <= Round.sin_up(iv.max())
#define NOT_GROWING(I) Round.sin_up(iv.min()) >= Round.sin_down(iv.max())
#define ASININF_DOWN Round.asin_down(aSinIv.min())
#define ASINSUP_UP Round.asin_up(aSinIv.max())
#define PI_UP pi_upper()
#define PI_DOWN pi_lower()
#define PITWICE_UP pi_twice_upper()
#define PITWICE_DOWN pi_twice_lower()

    int n = iv.max() / pi_twice_lower();
    // 0 <=> in [0;PI/2]
    // 1 <=> in [PI/2;PI]
    // 2 <=> in [PI;3*PI/2]
    // 3 <=> in [3*PI/2;2*PI]
    switch ( (POS(iv.min()) << 2) | POS(Round.sub_up(iv.max(),Round.mul_up(n,PITWICE_UP))) )
    {
      CASE_LABEL(0,0)
        if (GROWING(iv)) iv.assign(ASININF_DOWN,SHIFTN_UP(n,ASINSUP_UP));
        else  if (Round.sin_down(iv.min()) <= aSinIv.max())
                if (Round.sin_up(iv.max()) >= aSinIv.min()) break; // Nothing changed
                else iv.assign(iv.min(), SHIFTN_UP(n-1,Round.sub_up(PI_UP, ASININF_DOWN)));
              else
                if (Round.sin_up(iv.max()) >= aSinIv.min()) iv.assign(Round.sub_down(PI_DOWN, ASINSUP_UP), iv.max());
                else iv.assign(Round.sub_down(PI_DOWN, ASINSUP_UP), SHIFTN_UP(n-1,Round.sub_up(PI_UP, ASININF_DOWN)));
        break;
      CASE(0,1)
        if (GROWING(iv)) {
          if (Round.sin_down(iv.max()) <= aSinIv.max()) iv.assign(ASININF_DOWN, iv.max());
          else goto CASE_0_0;
        } else {
          if (Round.sin_down(iv.min()) <= aSinIv.max()) iv.assign(iv.min(), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
          else goto CASE_1_1;
        }
        break;
      CASE_LABEL(0,2)
        if (Round.sin_down(iv.min()) <= aSinIv.max()) iv.assign(iv.min(), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
        else goto CASE_1_2;
        break;
      CASE(0,3)
        if (Round.sin_down(iv.min()) <= aSinIv.max())
          if (Round.sin_up(iv.max()) >= aSinIv.min()) break; // Nothing changed
          else goto CASE_0_2;
        else goto CASE_1_3;
        break;
      CASE(1,0)
        if (GROWING(iv)) {
          if (Round.sin_up(iv.min()) >= aSinIv.min()) iv.assign(iv.min(), SHIFTN_UP(n,ASINSUP_UP));
          else iv.assign(Round.add_down(PITWICE_DOWN,ASININF_DOWN), SHIFTN_UP(n,ASINSUP_UP));
        } else {
          if (Round.sin_down(iv.max()) <= aSinIv.max()) iv.assign(Round.sub_down(PI_DOWN, ASINSUP_UP), iv.max());
          else { n--; goto CASE_1_1; }
        }
        break;
      CASE_LABEL(1,1)
        if (NOT_GROWING(iv)) iv.assign(Round.sub_down(PI_DOWN, ASINSUP_UP), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
        else  if (Round.sin_up(iv.min()) >= aSinIv.min())
                if (Round.sin_down(iv.max()) <= aSinIv.max()) break; // Nothing changed
                else iv.assign(iv.min(), SHIFTN_UP(n,ASINSUP_UP));
              else
                if (Round.sin_down(iv.max()) <= aSinIv.max()) iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN), iv.max());
                else iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN), SHIFTN_UP(n,ASINSUP_UP));
        break;
      CASE_LABEL(1,2) goto CASE_2_2;
      CASE_LABEL(1,3)
        if (Round.sin_up(iv.max()) >= aSinIv.min()) iv.assign(Round.sub_down(PI_DOWN, ASINSUP_UP), iv.max());
        else goto CASE_1_2;
        break;
      CASE_LABEL(2,0)
        if (Round.sin_up(iv.min()) >= aSinIv.min()) iv.assign(iv.min(), SHIFTN_UP(n,ASINSUP_UP));
        else iv.assign(Round.add_down(PITWICE_DOWN,ASININF_DOWN), SHIFTN_UP(n,ASINSUP_UP));
        break;
      CASE(2,1)
        if (Round.sin_up(iv.min()) >= aSinIv.min())
          if (Round.sin_down(iv.max()) <= aSinIv.max()) break; // Nothing changed
          else goto CASE_2_0;
        else goto CASE_3_0;
        break;
      CASE_LABEL(2,2)
        if (NOT_GROWING(iv)) iv.assign(Round.sub_down(PI_DOWN, ASINSUP_UP), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
        else  if (Round.sin_up(iv.min()) >= aSinIv.min())
                if (Round.sin_down(iv.max()) <= aSinIv.max()) break; // Nothing changed
                else iv.assign(iv.min(), SHIFTN_UP(n-1,Round.add_up(PITWICE_UP, ASINSUP_UP)));
              else
                if (Round.sin_down(iv.max()) <= aSinIv.max()) iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN), iv.max());
                else iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN), SHIFTN_UP(n-1,Round.add_up(PITWICE_UP, ASINSUP_UP)));
        break;
      CASE(2,3)
        if (GROWING(iv)) {
          if (Round.sin_up(iv.min()) >= aSinIv.min()) iv.assign(iv.min(), SHIFTN_UP(n,Round.add_up(PITWICE_UP, ASINSUP_UP)));
          else goto CASE_3_3;
        } else {
          if (Round.sin_up(iv.max()) >= aSinIv.min()) iv.assign(Round.sub_down(PI_DOWN, ASINSUP_UP), iv.max());
          else goto CASE_2_2;
        }
        break;
      CASE_LABEL(3,0) iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN), SHIFTN_UP(n,ASINSUP_UP)); break;
      CASE(3,1)
        if (Round.sin_down(iv.max()) <= aSinIv.max()) iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN), iv.max());
        else goto CASE_3_0;
        break;
      CASE(3,2)
        if (GROWING(iv)) {
          if (Round.sin_down(iv.max()) <= aSinIv.max()) iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN),iv.max());
          else { n--; goto CASE_3_3; }
        } else {
          if (Round.sin_down(iv.min()) <= aSinIv.max()) iv.assign(iv.min(), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
          else iv.assign(Round.add_down(PITWICE_DOWN, Round.sub_down(PI_DOWN, ASINSUP_UP)), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
        }
        break;
      CASE_LABEL(3,3)
        if (GROWING(iv)) iv.assign(Round.add_down(PITWICE_DOWN, ASININF_DOWN), SHIFTN_UP(n,Round.add_up(PITWICE_UP, ASINSUP_UP)));
        else  if (Round.sin_up(iv.min()) <= aSinIv.max())
                if (Round.sin_down(iv.max()) >= aSinIv.min()) break; // Nothing changed
                else iv.assign(iv.min(), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
              else
                if (Round.sin_down(iv.max()) >= aSinIv.min()) iv.assign(Round.sub_down(Round.add_down(PITWICE_DOWN,PI_DOWN), ASINSUP_UP), iv.max());
                else iv.assign(Round.sub_down(Round.add_down(PITWICE_DOWN,PI_DOWN), ASINSUP_UP), SHIFTN_UP(n,Round.sub_up(PI_UP, ASININF_DOWN)));
        break;
      default:
        GECODE_NEVER;
        break;
    }
#undef PI_UP
#undef PI_DOWN
#undef PITWICE_UP
#undef PITWICE_DOWN
#undef ASININF_DOWN
#undef ASINSUP_UP
#undef GROWING
#undef SHIFTN_UP
#undef SHIFTN_DOWN
#undef CASE_LABEL
#undef CASE
#undef POS
#undef I0__PI_2I
#undef IPI_2__PII
#undef IPI__3PI_2I
#undef I3PI_2__2PII
  }

  /*
   * Bounds consistent sinus operator
   *
   */

  template<class A, class B>
  forceinline
  Sin<A,B>::Sin(Home home, A x0, B x1)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,x0,x1) {}

  template<class A, class B>
  ExecStatus
  Sin<A,B>::post(Home home, A x0, B x1) {
    GECODE_ME_CHECK(x1.gq(home,-1.0));
    GECODE_ME_CHECK(x1.lq(home,1.0));
    (void) new (home) Sin<A,B>(home,x0,x1);
    return ES_OK;
  }


  template<class A, class B>
  forceinline
  Sin<A,B>::Sin(Space& home, bool share, Sin<A,B>& p)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,share,p) {}

  template<class A, class B>
  Actor*
  Sin<A,B>::copy(Space& home, bool share) {
    return new (home) Sin<A,B>(home,share,*this);
  }

  template<class A, class B>
  ExecStatus
  Sin<A,B>::propagate(Space& home, const ModEventDelta&) {
    GECODE_ME_CHECK(x1.eq(home,sin(x0.domain())));
    FloatVal iv = fmod(x0.domain(),FloatVal::pi_twice());
    FloatNum offSet(Round.sub_down(x0.min(),iv.min()));
    aSinProject(x1,iv);
    GECODE_ME_CHECK(x0.eq(home,iv + offSet));
    return (x0.assigned() && x1.assigned()) ? home.ES_SUBSUMED(*this) : ES_FIX;
  }


  /*
   * Bounds consistent cosinus operator
   *
   */

  template<class A, class B>
  forceinline
  Cos<A,B>::Cos(Home home, A x0, B x1)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,x0,x1) {}

  template<class A, class B>
  ExecStatus
  Cos<A,B>::post(Home home, A x0, B x1) {
    GECODE_ME_CHECK(x1.gq(home,-1.0));
    GECODE_ME_CHECK(x1.lq(home,1.0));
    (void) new (home) Cos<A,B>(home,x0,x1);
    return ES_OK;
  }


  template<class A, class B>
  forceinline
  Cos<A,B>::Cos(Space& home, bool share, Cos<A,B>& p)
    : MixBinaryPropagator<A,PC_FLOAT_BND,B,PC_FLOAT_BND>(home,share,p) {}

  template<class A, class B>
  Actor*
  Cos<A,B>::copy(Space& home, bool share) {
    return new (home) Cos<A,B>(home,share,*this);
  }

  template<class A, class B>
  ExecStatus
  Cos<A,B>::propagate(Space& home, const ModEventDelta&) {
    GECODE_ME_CHECK(x1.eq(home,cos(x0.domain())));
    FloatVal iv = fmod(FloatVal::pi_half() + x0.domain(),
                       FloatVal::pi_twice());
    FloatNum offSet(Round.sub_down(x0.min(),iv.min()));
    aSinProject(x1,iv);
    GECODE_ME_CHECK(x0.eq(home,iv + offSet));
    return (x0.assigned() && x1.assigned()) ? home.ES_SUBSUMED(*this) : ES_FIX;
  }

}}}

// STATISTICS: float-prop

