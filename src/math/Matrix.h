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
#include <common/Config.h>
#include <iostream>

namespace nspace
{
  
  template<typename T>
	class Matrix
	{
	public:
    virtual void toStream(std::ostream & s){
      for(int i=0; i < rows(); i++){
        for(int j=0; j < cols(); j++){
          s << (*this)(i,j) << ", ";
        }
        s << std::endl;

      }
    
    }
    virtual bool resize(int r, int c, bool setToZero){
      if(r==rows()&&c==cols())return true;
      return false;
    };


    virtual int rows () const = 0;
    virtual int cols () const = 0;
    virtual T& operator () (int i, int j) = 0;             // Zugriff per Index
    virtual const T& operator () (int i, int j) const = 0;
    virtual inline int size()const{
      return rows()*cols();
    }
  };
}