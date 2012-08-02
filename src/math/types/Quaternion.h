/*
 * IBDS - Impulse-Based Dynamic Simulation Library
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
#include <math/types/Vector3D.h>
#include <math/types/Matrix3x3.h>
#include <math/types/Matrix4x3.h>

namespace nspace
{
	/** Quaternion ist eine Klasse f�r Berechnungen mit einem Quaternion, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Quaternion
	{
	public:
		/** w-Komponente des Quaternions */
		Real w;
		/** x-Komponente des Quaternions */
		Real x;
		/** y-Komponente des Quaternions */
		Real y;
		/** z-Komponente des Quaternions */
		Real z;

	public:
	
    inline static Matrix4x3 Q(const Quaternion & q){
      Matrix4x3 ret;
      ret(0,0) =-q[1]; 
      ret(0,1) =-q[2];
      ret(0,2) =-q[3];
  
      ret(1,0) =q[0]; 
      ret(1,1) =-q[3];
      ret(1,2) =q[2];

      ret(2,0) =q[3]; 
      ret(2,1) =q[0];
      ret(2,2) =-q[1];

      ret(3,0) =-q[2]; 
      ret(3,1) =q[1];
      ret(3,2) =q[0];
      return ret;
      
    }
	inline static Quaternion transformAngularVelocity(const Vector3D & omega, const Quaternion & orientation){
      Quaternion qDot;
      qDot.w=0;
      qDot.x=omega[0];
      qDot.y=omega[1];
      qDot.z=omega[2];  
      qDot = 0.5*qDot*orientation;
      return qDot;
    }
	 inline Quaternion transformAngularVelocity(const Vector3D & omega)const{
      return Quaternion::transformAngularVelocity(omega,*this);
    }
   friend Quaternion operator * (const Matrix4x3& a, const Vector3D &v){
     Quaternion result(0,0,0,0);
     multiply(a,v,result);
     return result;
   }
   static inline void multiply(const Matrix4x3 & a, const Vector3D & v, Quaternion & result){
    result.w= 0; result.x=0; result.y=0; result.z=0;
     for(int i=0; i < 3; i++){
       result.w += v(i)*a(0,i);
       result.x += v(i)*a(1,i);
       result.y += v(i)*a(2,i);
       result.z += v(i)*a(3,i);
     }
   }
	 inline static Vector3D transformAngularVelocity(const Quaternion& qDot, const Quaternion & orientation){
      Quaternion conj = orientation.conjugate();
      Quaternion omegaTilde = 2*conj*qDot;
      return Vector3D(omegaTilde.x,omegaTilde.y,omegaTilde.z);
    }
    inline Vector3D transformAngularVelocity(const Quaternion & qDot)const{
      return Quaternion::transformAngularVelocity(qDot,*this);
    }
    static Quaternion axisAngle(const Vector3D & axis, Real angle){
      Quaternion ret;
      ret.setFromAxisAngle(axis,angle);
      return ret;
    }
    Quaternion(const Real * elements){assign(elements);}
		Quaternion();
		Quaternion(const Real pw, const Real px, const Real py, const Real pz);
		void setFromAxisAngle (const Vector3D &axis, const Real angle);
		void getAxisAngle (Vector3D &axis, Real &angle);
		void setFromMatrix3x3 (Matrix3x3 *m);
		void getMatrix3x3 (Matrix3x3 &m)const;
		void setFromMatrix3x3T (Matrix3x3 *m);
		void getMatrix3x3T (Matrix3x3 &m)const;
		void normalize ();
		Real length ();
		Real length2 ();
		Quaternion conjugate ()const;

    inline void assign(const Real * elements){
      w = elements[0];
      x = elements[1];
      y = elements[2];
      z = elements[3];
    }
    inline void copyTo(Real * elements)const{
      elements[0]=w;
      elements[1]=x;
      elements[2]=y;
      elements[3]=z;
    }
    static const Quaternion & zeroRotation();

    Matrix3x3 getMatrix3x3()const{
      Matrix3x3 result;
      getMatrix3x3(result);
      return result;
    }
		friend Quaternion operator - (const Quaternion& a);							// -m1
		friend Quaternion operator + (const Quaternion& a, const Quaternion& b);	// m1 + m2
		friend Quaternion operator - (const Quaternion& a, const Quaternion& b);	// m1 - m2
		friend Quaternion operator * (const Quaternion& a, const Quaternion& b);	// a * b
		friend Quaternion operator * (const Real d, const Quaternion& a);			// d * a
    friend Quaternion operator * (const Quaternion & a, const Real d){return d*a;}
		friend Quaternion operator | (const Vector3D& a, const Quaternion& b);		// (0,a^T) * b
		friend Quaternion operator | (const Quaternion& a, const Vector3D& b);		// a * (0,b^T)
		Quaternion& operator = (const Quaternion& q);								// Zuweisung
    FORCE_INLINE Real& Quaternion::operator [] (const int i)
    {
      switch(i)
      {
      case 0: return w;
      case 1: return x;
      case 2: return y;
      case 3: return z;
      }
      return w;
    }

    FORCE_INLINE Real& Quaternion::operator () (const int i)
    {
      switch(i)
      {
      case 0: return w;
      case 1: return x;
      case 2: return y;
      case 3: return z;
      }
      return w;
    }

    FORCE_INLINE const Real& Quaternion::operator [] (const int i) const
    {
      switch(i)
      {
      case 0: return w;
      case 1: return x;
      case 2: return y;
      case 3: return z;
      }
      return w;
    }

    FORCE_INLINE const Real& Quaternion::operator () (const int i) const
    {
      switch(i)
      {
      case 0: return w;
      case 1: return x;
      case 2: return y;
      case 3: return z;
      }
      return w;
    }

		friend std::ostream& operator << (std::ostream& s, Quaternion& q);					// Streamausgabe
	};
}


