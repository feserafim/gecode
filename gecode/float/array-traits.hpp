/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Vincent Barichard <Vincent.Barichard@univ-angers.fr>
 *
 *  Copyright:
 *     Christian Schulte, 2005
 *     Vincent Barichard, 2012
 *
 *  Last modified:
 *     $Date: 2012-03-28 23:47:11 +0900 (水, 28 3 2012) $ by $Author: vbarichard $
 *     $Revision: 12648 $
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

  class FloatVarArgs;
  class FloatVarArray;
  class FloatArgs;
  
  /// Traits of %FloatVarArgs
  template<>
  class ArrayTraits<VarArgArray<FloatVar> > {
  public:
    typedef FloatVarArgs StorageType;
    typedef FloatVar     ValueType;
    typedef FloatVarArgs ArgsType;
  };

  /// Traits of %FloatVarArray
  template<>
  class ArrayTraits<VarArray<FloatVar> > {
  public:
    typedef FloatVarArray  StorageType;
    typedef FloatVar       ValueType;
    typedef FloatVarArgs   ArgsType;
  };

  /// Traits of %FloatArgs
  template<>
  class ArrayTraits<PrimArgArray<FloatNum> > {
  public:
    typedef FloatArgs StorageType;
    typedef FloatNum  ValueType;
    typedef FloatArgs ArgsType;
  };

  /// Traits of %FloatVarArray
  template<>
  class ArrayTraits<FloatVarArray> {
  public:
    typedef FloatVarArray  StorageType;
    typedef FloatVar       ValueType;
    typedef FloatVarArgs   ArgsType;
  };
  
  /// Traits of %FloatVarArgs
  template<>
  class ArrayTraits<FloatVarArgs> {
  public:
    typedef FloatVarArgs StorageType;
    typedef FloatVar     ValueType;
    typedef FloatVarArgs ArgsType;
  };

  /// Traits of %FloatArgs
  template<>
  class ArrayTraits<FloatArgs> {
  public:
    typedef FloatArgs StorageType;
    typedef FloatNum  ValueType;
    typedef FloatArgs ArgsType;
  };
  
}

// STATISTICS: float-other
