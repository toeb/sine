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

#ifndef __MATRIX3X3_H__
#define __MATRIX3X3_H__

#include "Common/Config.h"
#include "Matrix.h"
#include "Vector3D.h"

namespace nspace
{
	/** Matrix3x3 ist eine Klasse für Berechnungen mit einer 3x3 Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Matrix3x3 : public Matrix
	{
	public:
		/** Zeilenvektoren der 3x3 Matrix */
		Vector3D v[3];

	public:
    inline Vector3D col(int index)const{
      return this->transpose().row(index);
    }
    inline Vector3D row(int index)const{
      return v[index];
    }
   Matrix3x3(Real fillValue);

    Matrix3x3(Real a11, Real a22, Real a33);
    Matrix3x3(const Matrix3x3 & rhs);
		Matrix3x3();
		Matrix3x3(const Vector3D &v0, const Vector3D &v1, const Vector3D &v2);
    ~Matrix3x3();

    void setIdentity(){
      for(int i=0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          (*this)(i,j)=0;
          if(i==j)(*this)(i,j)=1;
        }
      }
    }
    
    inline void transposeInPlace(){
      Real tmp;
      tmp = v[0].v[1]; v[0].v[1] = v[1].v[0]; v[1].v[0] = tmp;
      tmp = v[0].v[2]; v[0].v[2] = v[2].v[0]; v[2].v[0] = tmp;      
      tmp = v[1].v[2]; v[1].v[2] = v[2].v[1]; v[2].v[1] = tmp;
    }
    //my methods
    void getCoordinateVectors(Vector3D & direction, Vector3D & normal, Vector3D & binormal)const{
      Matrix3x3 t = transpose();
      direction.assign(t.v[0]);
      normal.assign(t.v[1]);
      binormal.assign(t.v[2]);


    }

    
    
    inline static void symmInverse(const Matrix3x3 & m, Matrix3x3 & m_inverted){
      const Vector3D * v = m.v;
      Real e2_df = v[1].v[2]*v[1].v[2] - v[1].v[1]*v[2].v[2];  // e^2 - d*f
	    Real bf = v[0].v[1]*v[2].v[2];
	    Real ce = v[0].v[2]*v[1].v[2];
	    Real c2 = v[0].v[2]*v[0].v[2];
	    Real cd = v[0].v[2]*v[1].v[1];
	    Real be = v[0].v[1]*v[1].v[2];
	    Real af = v[0].v[0]*v[2].v[2];
	    Real ae = v[0].v[0]*v[1].v[2];
	    Real bc = v[0].v[1]*v[0].v[2];
	    Real b2 = v[0].v[1]*v[0].v[1];
	    Real ad = v[0].v[0]*v[1].v[1];

	    Real Div = 1.0 / (c2*v[1].v[1] + v[0].v[1] * (bf - 2 * ce) + v[0].v[0]* e2_df  );

	    Real a = e2_df * Div;
	    Real b = (bf - ce) * Div;
	    Real c = (cd - be) * Div;
	    Real d = (c2 - af) * Div;
	    Real e = (ae - bc) * Div;
	    Real f = (b2 - ad) * Div;
      m_inverted(0,0)=a;
      m_inverted(0,1)=b;
      m_inverted(0,2)=c;
  
      m_inverted(1,0)=b;
      m_inverted(1,1)=d;
      m_inverted(1,2)=e;
  
      m_inverted(2,0)=c;
      m_inverted(2,1)=e;
      m_inverted(2,2)=f;
    }
    inline void setZero();
    inline void setTo(Real value);
    static inline void multiply(const Matrix3x3 & a, const Matrix3x3 & b, Matrix3x3  &c);
    static inline void transpose(const Matrix3x3 & a, Matrix3x3 & aT){
  aT.v[0].v[0] = a.v[0].v[0]; aT.v[0].v[1] = a.v[1].v[0]; aT.v[0].v[2] = a.v[2].v[0];  
  aT.v[1].v[0] = a.v[0].v[1]; aT.v[1].v[1] = a.v[1].v[1]; aT.v[1].v[2] = a.v[2].v[1];  
  aT.v[2].v[0] = a.v[0].v[2]; aT.v[2].v[1] = a.v[1].v[2]; aT.v[2].v[2] = a.v[2].v[2];
}
    static inline void subtract(const Matrix3x3 & a, const Matrix3x3 & b, Matrix3x3 &c){
      c.v[0].v[0] = a.v[0].v[0]-b.v[0].v[0];
      c.v[0].v[1] = a.v[0].v[1]-b.v[0].v[1];
      c.v[0].v[2] = a.v[0].v[2]-b.v[0].v[2];
      c.v[1].v[0] = a.v[1].v[0]-b.v[1].v[0];
      c.v[1].v[1] = a.v[1].v[1]-b.v[1].v[1];
      c.v[1].v[2] = a.v[1].v[2]-b.v[1].v[2];
      c.v[2].v[0] = a.v[2].v[0]-b.v[2].v[0];
      c.v[2].v[1] = a.v[2].v[1]-b.v[2].v[1];
      c.v[2].v[2] = a.v[2].v[2]-b.v[2].v[2];
    }
    static const Matrix3x3 & Zero();
    static const Matrix3x3 & Identity();
    
    
    bool isZero();

    friend bool operator ==(const Matrix3x3& a, const Matrix3x3& b); 
    friend bool operator !=(const Matrix3x3& a, const Matrix3x3& b); 

		friend Matrix3x3 operator - (const Matrix3x3& a);						// -m1
		friend Matrix3x3 operator + (const Matrix3x3& a, const Matrix3x3& b);	// m1 + m2
		friend Matrix3x3 operator - (const Matrix3x3& a, const Matrix3x3& b);	// m1 - m2
		friend Matrix3x3 operator * (const Matrix3x3& a, const Matrix3x3& b);	// a * b
    

		friend Matrix3x3 operator * (const Real d, const Matrix3x3& a);			// d * a

		friend Vector3D operator * (const Vector3D& v, const Matrix3x3& m);

		friend std::ostream& operator << (std::ostream& s, const Matrix3x3& m);					// Streamausgabe

		Vector3D& operator [] ( int i);							// Zugriff per Index
		const Vector3D& operator [] ( int i) const;
		virtual Real& operator () (int i, int j);				// Zugriff per Index
		virtual const Real& operator () (int i, int j) const;

		virtual int getRows () const;
		virtual int getCols () const;

    /**
     * \brief Assigns this matrix the values of m
     *
     * \author Tobi
     * \date 10.05.2012
     *
     * \param m The m.
     */
    void assign(const Matrix3x3 & m);

		Matrix3x3 transpose() const;								// Transponiert die 3x3-Matrix
		Matrix3x3 inverse () const;								// Invertiert die Matrix
		Matrix3x3 symmInverse () const;							// Invertiert eine symmetrische Matrix
	};
}

#endif


