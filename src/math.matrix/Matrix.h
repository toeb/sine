/*
* nspace - Impulse-Based Dynamic Simulation Library
* Copyright (c) 2003-2008 Jan Bender http://www.impulse-based.de
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
* Jan Bender - Jan.Bender@impulse-based.de
*/

#pragma once
#include <config.h>
#include <iostream>
#include <math.matrix/MatrixOperations.h>

namespace nspace
{

  template<typename T, typename IndexType=int, typename SizeType = int>
  class Matrix
  {
  public:
    typedef IndexType Index;
    typedef SizeType Size;
    typedef T ElementType;
    
    Matrix(){}

    template<typename MatrixType>
    operator MatrixType()const{
      MatrixType result;
      MatrixAssign<MatrixType,Matrix<T>>::operation(result,*this);
      return result;
    }

    virtual void toStream(std::ostream & s)const{
      for(Index i=0; i < rows(); i++){
        for(Index j=0; j < cols(); j++){
          s << (*this)(i,j) << ", ";
        }
        s << std::endl;

      }

    }
    virtual bool resize(Index r, Index c){
      if(r==rows()&&c==cols())return true;
      return false;
    };



    



    virtual Size rows () const = 0;
    virtual Size cols () const = 0;
    virtual T& operator () (Index i,Index j) = 0;             // Zugriff per Index
    virtual const T& operator () (Index i, Index j) const = 0;
    virtual inline Size size()const{
      return rows()*cols();
    }
  };

  //template<typename T, typename IndexType=int, typename SizeType = int>
  template<typename T, typename IndexType, typename SizeType>
  class MatrixCoefficient<Matrix<T,IndexType,SizeType>>{
  public:
    typedef T Type;
  };
  template<typename T, typename IndexType, typename SizeType>
  class MatrixIndex<Matrix<T,IndexType,SizeType>>{
  public:
    typedef IndexType Type;
  };
  template<typename T, typename IndexType, typename SizeType>
  class MatrixSize<Matrix<T,IndexType,SizeType>>{
  public:
    typedef SizeType Type;
  };
}