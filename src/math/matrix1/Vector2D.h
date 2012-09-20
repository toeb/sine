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
#include <math/Vector.h>
#include "Vector3D.h"
#include <iostream>
#include <cmath>

namespace nspace{
	class Matrix2x2;

	/** Vector2D ist eine Klasse für Vektorberechnungen, wie z.B. Addition, Kreuzprodukt,...
	  \author Jan Bender
	  */
	class Vector2D : public nspace::Vector<Real>
	{
	public:
		/** Komponenten des Vektors */
		Real v[2];
	public:
		Vector2D(const Real x, const Real y);
		Vector2D();
		Vector2D(const Vector3D vec);

		friend Vector2D operator - (const Vector2D& v);						  // -v1
		friend Vector2D operator + (const Vector2D& a, const Vector2D& b);	  // v1 + v2
		friend Vector2D operator - (const Vector2D& a, const Vector2D& b);	  // v1 - v2
		friend Vector2D operator * (const Vector2D& a, const Real d);		  // v1 * 3.0
		friend Vector2D operator * (const Real d, const Vector2D& a);		  // 3.0 * v1
		friend Vector2D operator | (const Vector2D& a, const Vector2D& b);    // degenerierte Matrixmultiplikation
		friend Real operator * (const Vector2D& a, const Vector2D& b);	  // Skalarprodukt
		friend Vector2D operator * (const Vector2D& v, const Matrix2x2& m);	  // v * M
		friend Vector2D operator * (const Matrix2x2& m, const Vector2D& v);	  // M * v
		friend Matrix2x2 operator * (const Matrix2x2& a, const Matrix2x2& b);		      // Matrix3x3-Produkt
		friend bool operator == (const Vector2D &a, const Vector2D &b);		  // a == b ?
		friend bool operator != (const Vector2D &a, const Vector2D &b);		  // a == b ?
		friend bool operator < (const Vector2D &a, const Vector2D &b);		  // a < b: hat geringeren Abstand zum Nullpunkt


		Vector2D& operator = ( const Vector2D& v );					// Zuweisung
		Vector2D& operator -= (const Vector2D& v);					// Subtraktion
		Vector2D& operator += (const Vector2D& v);					// Addition
		Vector2D& operator *= ( const Real d );					// Multiplikation mit einer Konstanten 
		Vector2D& operator /= ( const Real d );					// Division mit einer Konstanten
		

		friend std::ostream& operator << (std::ostream& s, const Vector2D& v);	    // Streamausgabe


		Real distance (const Vector2D & a) const;   // Abstand zum Punkt a
		Real distance2 (const Vector2D & a) const;  // Quadratischer Abstand zum Punkt a

    //Matrix Members
		inline int rows () const{return 2;}		
    inline int cols () const{return 1;}
    inline Real& operator () (int i, int j){return v[i];}
    inline const Real& operator () (int i, int j) const{return v[j];}
    //Vector members
    inline Real & operator()(int i){return v[i];};
    inline const Real &operator()(int i)const{return v[i];};
    inline int size()const{return 2;};
    inline Real length() const{return std::sqrt(length2());}
    inline Real length2() const{return v[0]*v[0]+v[1]*v[1];}
    inline void normalize(){Real l = length(); v[0] = v[0]/l; v[1]=v[1]/l;}


		friend class Matrix2x2;
	};
  }


