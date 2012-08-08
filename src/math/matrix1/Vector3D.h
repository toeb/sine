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

#include <common/config.h>
#include <math/Vector.h>
#include <iostream>



namespace nspace{
	class Matrix3x3;
	class Vector1D;
  
	/** Vector3D ist eine Klasse für Vektorberechnungen, wie z.B. Addition, Kreuzprodukt,...
	  \author Jan Bender
	  */
  
	class Vector3D : public nspace::Vector<Real>
	{
	public:
		/** Komponenten des Vektors */
		Real v[3];

	public:
    static const Vector3D & Ones();
    static const Vector3D & UnitX();
    static const Vector3D & UnitY();
    static const Vector3D & UnitZ();
    inline Real maxValue()const{
      Real m=x();
      if(m < y())m=y();
      if(m< z())m=z();
      return m;

    }
    inline Real maximum()const{
      return maxValue();
    }
    inline const Real & x()const{
      return v[0];
    }
    inline const Real & y()const{
      return v[1];
    }
    inline const Real & z()const{
      return v[2];
    }
    inline  Real & x(){
      return v[0];
    }
    inline  Real & y(){
      return v[1];
    }
    inline  Real & z(){
      return v[2];
    }
		void set(Real x, Real y, Real z){
      v[0]=x;
      v[1]=y;
      v[2]=z;
    }
    void assign(const Vector3D &vector);
    Vector3D(const Real x, const Real y, const Real z);
		Vector3D();
		Vector3D(const Vector3D &vector);
		Vector3D(const Real * elements){
      assign(elements);
    }
    ~Vector3D();

    inline void assign(const Real * elements){
      v[0]=elements[0];
      v[1]=elements[1];
      v[2]=elements[2];
    }
    inline void copyTo(Real * elements)const{
     elements[0] =v[0];
     elements[1] =v[1];
     elements[2] =v[2];
    }

    static inline void toBarycentricCoordinates(const Vector3D & p, const Vector3D & x1, const Vector3D & x2, const Vector3D & x3, Vector3D & uvw){
      Vector3D n1,n2,n3;
      Vector3D r;
      
      subtract(x2,x1,n1);
      subtract(x3,x1,n2);
      subtract(p,x1,r);
      
      n1.normalize();
      n2.normalize();
      crossProduct(n1,n2,n3);
      
      dotProduct(n1,r,uvw.v[0]);
      dotProduct(n2,r,uvw.v[1]);
      dotProduct(n3,r,uvw.v[2]);
    }

    //inline mehtods for performance critical sections
    //b = s*a
    inline static void multiplyScalar(Real s, const Vector3D & a, Vector3D & b){
      b.v[0] = s*a.v[0];
      b.v[1] = s*a.v[1];
      b.v[2] = s*a.v[2];
    }
    inline static void dotProduct(const Vector3D & a, const Vector3D & b, Real & c){
      c= a.v[0]*b.v[0]+a.v[1]*b.v[1]+a.v[2]*b.v[2];
    }
    //c = a-b
    inline static void subtract(const Vector3D & a, const Vector3D & b, Vector3D & c){
      c.v[0] = a.v[0]-b.v[0];
      c.v[1] = a.v[1]-b.v[1];
      c.v[2] = a.v[2]-b.v[2];
    }
    
    inline static void add(const Vector3D & a, const Vector3D & b, Vector3D & c){
      c.v[0] = a.v[0]+b.v[0];
      c.v[1] = a.v[1]+b.v[1];
      c.v[2] = a.v[2]+b.v[2];
    }
    inline static void crossProduct(const Vector3D & a, const Vector3D & b,Vector3D & c){
      c.v[0] = a.v[1]*b.v[2]-a.v[2]*b.v[1];
      c.v[1] = a.v[2]*b.v[0]-a.v[0]*b.v[2];
      c.v[2] = a.v[0]*b.v[1]-a.v[1]*b.v[0];
    }
    inline static void signum(const Vector3D& a, Vector3D & b){
      b.v[0]=1;
      b.v[1]=1;
      b.v[2]=1;
      
      if(a.v[0]<0)b.v[0]=-1;
      if(a.v[1]<0)b.v[1]=-1;
      if(a.v[2]<0)b.v[2]=-1;

    }

    static const Vector3D & Zero();
    void setZero();
		friend Vector3D operator - (const Vector3D& v);						  // -v1
		friend Vector3D operator + (const Vector3D& a, const Vector3D& b);	  // v1 + v2
		friend Vector3D operator - (const Vector3D& a, const Vector3D& b);	  // v1 - v2
		friend Vector3D operator * (const Vector3D& a, const Real d);		  // v1 * 3.0
		friend Vector3D operator * (const Real d, const Vector3D& a);		  // 3.0 * v1
		friend Vector3D operator | (const Vector3D& a, const Vector3D& b);    // degenerierte Matrixmultiplikation
		friend Real operator * (const Vector3D& a, const Vector3D& b);		  // Skalarprodukt
		friend Vector3D operator * (const Vector3D& v, const Matrix3x3& m);	  // v * M
		friend Vector3D operator * (const Matrix3x3& m, const Vector3D& v);	  // M * v
		friend Vector3D operator * (const Vector3D& v, const Vector1D& m);	  // v * M
		friend Vector3D operator * (const Vector1D& m, const Vector3D& v);	  // M * v

		friend Vector3D operator ^ (const Vector3D& a, const Vector3D& b);	  // Kreuzprodukt
		friend Matrix3x3 operator , (const Matrix3x3& m, const Vector3D& v);  // M , v
		friend Matrix3x3 operator , (const Vector3D& v, const Matrix3x3& m);  // M , v
		friend Matrix3x3 operator * (const Matrix3x3& a, const Matrix3x3& b); // Matrix3x3-Produkt
		friend bool operator == (const Vector3D &a, const Vector3D &b);		  // a == b ?
		friend bool operator != (const Vector3D &a, const Vector3D &b);		  // a == b ?
		friend bool operator < (const Vector3D &a, const Vector3D &b);		  // a < b: hat geringeren Abstand zum Nullpunkt
    Vector3D & copy();

		Vector3D& operator = ( const Vector3D& v );					// Zuweisung
		Vector3D& operator -= (const Vector3D& v);					// Subtraktion
		Vector3D& operator += (const Vector3D& v);					// Addition
		Vector3D& operator *= ( const Real d );					    // Multiplikation mit einer Konstanten 
		Vector3D& operator /= ( const Real d );					    // Division mit einer Konstanten
  
    //vector members
    virtual inline Real & operator()(int i){
      return v[i];
    }
    virtual inline const Real & operator()(int i)const{
      return v[i];
    }

		
		virtual Real& operator () (int i, int j);					// Zugriff per Index
		virtual const Real& operator () (int i, int j) const;

		friend std::ostream& operator << (std::ostream& s, const Vector3D& v);	    // Streamausgabe

		virtual Real length() const;	    // Länge
		virtual Real length2() const;		// Quadratische Länge
		virtual void normalize();		// Normierung 
		Real distance (const Vector3D &a) const;   // Abstand zum Punkt a
		Real distance2 (const Vector3D &a) const;  // Quadratischer Abstand zum Punkt a

    inline int size()const{return 3;}
    inline int rows()const{return 3;}
    inline int cols()const{return 1;}
		friend class Matrix3x3;
	};
}

