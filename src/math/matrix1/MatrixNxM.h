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
#include <cstring>
#include <cmath>
#include <math/matrix1/DynamicMatrix.h>
#include <math/matrix1/VectorND.h>
#include <functional>
namespace nspace
{
	/** MatrixNxM ist eine Klasse für Berechnungen mit einer nxm Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class MatrixNxM : public DynamicMatrix<Real>
	{
  private:
//     Real * _data;
//     /** Zeilenvektoren der 2x2 Matrix */
// 
//     /* Anzahl Zeilen */
//     int _rows;
//     /* Anzahl Spalten */
//     int _cols;

	public:
    inline int size()const{return _rows*_cols;}
    void setZero(){
      memset(_data,0,sizeof(Real)*size());
      /*for(int i=0; i < rows(); i++){
        for(int j=0; j < cols(); j++){
          value(i,j)=0.0;
        }
      }*/
    }
    void setFunction(std::function<void (Real & ,int,int) > f){
      int size = _rows*_cols;
      for(int i=0; i < size; ++i){
        f(_data[i],i/_cols, i%_cols);
      }
    }
    void setConstant(const Real & value){
      int size = _rows*_cols;
      for(int i=0; i < size; ++i){
        _data[i]=value;
      }
    }

    //returns the frobenius norm
    Real norm(){

      Real sum=0;
      for(int i=0;i<_rows;i++){
        for(int j=0; j < _cols; j++){
          sum+=value(i,j)*value(i,j);
        }
      }
      return std::sqrt(sum);
    }
	public:
    MatrixNxM(){}    
    MatrixNxM(const int rows, const int cols);
// 		MatrixNxM (const MatrixNxM& copy);
// 		~MatrixNxM();

		friend MatrixNxM operator - (const MatrixNxM& a);						// -m1
		friend MatrixNxM operator + (const MatrixNxM& a, const MatrixNxM& b);	// m1 + m2
		friend MatrixNxM operator - (const MatrixNxM& a, const MatrixNxM& b);	// m1 - m2
		friend MatrixNxM operator * (const MatrixNxM& a, const MatrixNxM& b);	// a * b
		friend MatrixNxM operator * (const Real d, const MatrixNxM& a);		// d * a
    friend MatrixNxM operator * (const MatrixNxM & a, const Real d){return d*a;}
    friend MatrixNxM operator / (const MatrixNxM & a, const Real d){return (1.0/d)*a;}
		


		friend VectorND operator * (const VectorND& v, const MatrixNxM& m);
    
    
		VectorND& operator [] ( int i);							// Zugriff per Index
		const VectorND& operator [] ( int i) const;
		

		friend std::ostream& operator << (std::ostream& s, const MatrixNxM& m);	// Streamausgabe



		MatrixNxM transpose() const;									
		void zero ();
		bool inverse ();

		friend class VectorND;
	};
}




