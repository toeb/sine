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

#include "Common/Config.h"
#include "Vector.h"
#include "Vector3D.h"
#include <iostream>

namespace nspace
{
	/** Vector1D ist eine Klasse für Vektorberechnungen, wie z.B. Addition, Kreuzprodukt,...
	  \author Jan Bender
	  */
	class Vector1D : public Vector<Real>
	{
	public:
		/** Komponenten des Vektors */
		Real v;

	public:
		Vector1D(const Real x);
		Vector1D();
		Vector1D(const Vector3D vec);

		friend Vector1D operator - (const Vector1D& v);						  // -v1
		friend Vector1D operator + (const Vector1D& a, const Vector1D& b);	  // v1 + v2
		friend Vector1D operator - (const Vector1D& a, const Vector1D& b);	  // v1 - v2
		friend Vector1D operator * (const Vector1D& a, const Real d);		  // v1 * 3.0
		friend Vector1D operator * (const Real d, const Vector1D& a);		  // 3.0 * v1
		friend Vector1D operator | (const Vector1D& a, const Vector1D& b);    // degenerierte Matrixmultiplikation
		friend Real operator * (const Vector1D& a, const Vector1D& b);	  // Skalarprodukt
		friend bool operator == (const Vector1D &a, const Vector1D &b);		  // a == b ?
		friend bool operator != (const Vector1D &a, const Vector1D &b);		  // a == b ?
		friend bool operator < (const Vector1D &a, const Vector1D &b);		  // a < b: hat geringeren Abstand zum Nullpunkt



		Vector1D& operator = ( const Real& s );					// Zuweisung
		Vector1D& operator = ( const Vector1D& v );					// Zuweisung
		Vector1D& operator -= (const Vector1D& v);					// Subtraktion
		Vector1D& operator += (const Vector1D& v);					// Addition
		Vector1D& operator *= ( const Real d );					// Multiplikation mit einer Konstanten 
		Vector1D& operator /= ( const Real d );					// Division mit einer Konstanten

		virtual Real& operator () (int i, int j);					// Zugriff per Index
		virtual const Real& operator () (int i, int j) const;

		friend std::ostream& operator << (std::ostream& s, const Vector1D& v);	    // Streamausgabe

		virtual Real length() const;		// Länge
		virtual Real length2() const;		// Quadratische Länge
		virtual void normalize();		// Normierung 
		Real distance (Vector1D a) const;   // Abstand zum Punkt a
		Real distance2 (Vector1D a) const;  // Quadratischer Abstand zum Punkt a

    inline int rows () const{return 1;}
    inline int cols () const{return 1;}
    inline int size()const{return 1;}

    inline Real& operator () (int i){return v;}
    inline const Real& operator () (int i)const{return v;};
   
		friend class Matrix2x2;
	};
}

