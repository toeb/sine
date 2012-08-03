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
#include <math/types/Matrix.h>


namespace nspace
{
  

	/** Matrix4x4 ist eine Klasse für Berechnungen mit einer 4x4 Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Matrix4x3 : public Matrix
	{
	public:
		/** Zeilenvektoren der 4x3 Matrix */
		Real m[4][3]; 

	public:
    Matrix4x3(){}
    Matrix4x3(Real matrix[4][3]){
      for(int i=0; i < 4; i++){
        for(int j=0; j < 3; j++){
          m[i][j]=matrix[i][j];
        }
      }
    }

		friend Matrix4x3 operator - (const Matrix4x3& a){
      Matrix4x3 result;
      for(int i=0; i < 4; i++){
        for(int j=0; j < 3; j++){
          result.m[i][j]=-a.m[i][j];
        }
      }
      return result;
    };						// -m1
		friend Matrix4x3 operator + (const Matrix4x3& a, const Matrix4x3& b){
      Matrix4x3 result;
      for(int i=0; i < 4; i++){
        for(int j=0; j < 3; j++){
          result.m[i][j]=a.m[i][j]+b.m[i][j];
        }
      }
      return result;
    }

  
		friend Matrix4x3 operator - (const Matrix4x3& a, const Matrix4x3& b){
      return a + (-b);
    }


		friend Matrix4x3 operator * (const Real d, const Matrix4x3& a){
      Matrix4x3 result;
      for(int i=0; i < 4; i++){
        for(int j=0; j < 3; j++){
          result.m[i][j]=a.m[i][j]*d;
        }
      }
      return result;
    }
   

		Matrix4x3& operator = ( const Matrix4x3& a){
      for(int i=0; i < 4; i++){
        for(int j=0; j < 3; j++){
          m[i][j]=a.m[i][j];
        }
      }
      return *this;
    }


    virtual Real& operator () (int i, int j){return m[i][j];}
		const virtual Real& operator () (int i, int j) const{return m[i][j];}

		inline int rows () const{return 4;}
		inline int cols () const{return 3;}



	};
}



