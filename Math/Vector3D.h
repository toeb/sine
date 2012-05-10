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

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include "Common/Config.h"
#include "Vector.h"
#include <iostream>
#include "MathDefs.h"


namespace IBDS
{
	class Matrix3x3;
	class Vector1D;

	/** Vector3D ist eine Klasse für Vektorberechnungen, wie z.B. Addition, Kreuzprodukt,...
	  \author Jan Bender
	  */
	class Vector3D : public Vector
	{
	public:
		/** Komponenten des Vektors */
		Real v[3];

	public:
		void assign(const Vector3D &vector);
    Vector3D(const Real x, const Real y, const Real z);
		Vector3D();
		Vector3D(const Vector3D &vector);
    ~Vector3D();
    static const Vector3D & Zero();
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
		virtual Real& operator [] (int i);						// Zugriff per Index
		virtual const Real& operator [] (int i) const;
		virtual Real& operator () (int i, int j);					// Zugriff per Index
		virtual const Real& operator () (int i, int j) const;

		friend std::ostream& operator << (std::ostream& s, const Vector3D& v);	    // Streamausgabe

		virtual Real length() const;	    // Länge
		virtual Real length2() const;		// Quadratische Länge
		virtual void normalize();		// Normierung 
		Real distance (const Vector3D &a) const;   // Abstand zum Punkt a
		Real distance2 (const Vector3D &a) const;  // Quadratischer Abstand zum Punkt a

		virtual int getRows () const;
		virtual int getCols () const;

		friend class Matrix3x3;
	};
}

#endif

