/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Vincent Barichard <Vincent.Barichard@univ-angers.fr>
 *
 *  Copyright:
 *     Vincent Barichard, 2012
 *
 *  Last modified:
 *     $Date: 2012-03-28 03:43:27 +0900 (水, 28 3 2012) $ by $Author: schulte $
 *     $Revision: 12642 $
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

namespace Gecode {

  /*
   * Operations for linear float relations
   *
   */
  forceinline
  LinFloatRel::LinFloatRel(void) {}

  forceinline
  LinFloatRel::LinFloatRel(const LinFloatExpr& l, FloatRelType frt0, const LinFloatExpr& r)
    : e(l-r), frt(frt0) {}

  forceinline
  LinFloatRel::LinFloatRel(const LinFloatExpr& l, FloatRelType frt0, FloatVal r)
    : e(l-r), frt(frt0) {}

  forceinline
  LinFloatRel::LinFloatRel(FloatVal l, FloatRelType frt0, const LinFloatExpr& r)
    : e(l-r), frt(frt0) {}

  forceinline void
  LinFloatRel::post(Home home, bool t) const {
    if (t)
      e.post(home,frt);
    else
    {
      BoolVar b(home,t,t);
      e.post(home,frt,b,true);
    }
  }

  forceinline void
  LinFloatRel::post(Home home, const BoolVar& b, bool t) const {
    e.post(home,frt,b,t);
  }

}

// STATISTICS: minimodel-any
