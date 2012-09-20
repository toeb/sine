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

#ifndef __MATRIX3X2_H__
#define __MATRIX3X2_H__

#include <config.h>
#include <math/Matrix.h>
#include "Matrix2x3.h"
#include "Vector3D.h"

namespace nspace{
	/** Matrix3x2 ist eine Klasse für Berechnungen mit einer 3x3 Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Matrix3x2 : public nspace::Matrix<Real>
	{
	public:
		/** Zeilenvektoren der 3x2 Matrix */
		Vector2D v[3];

	public:
		Matrix3x2();
		Matrix3x2(const Vector2D& v0, const Vector2D &v1, const Vector2D &v2);

		friend Matrix3x2 operator - (const Matrix3x2& a);						// -m1
		friend Matrix3x2 operator + (const Matrix3x2& a, const Matrix3x2& b);	// m1 + m2
		friend Matrix3x2 operator - (const Matrix3x2& a, const Matrix3x2& b);	// m1 - m2
		friend Matrix3x2 operator * (const Matrix3x2& a, const Matrix2x2& b);	// a * b
		friend Matrix3x2 operator * (const Matrix3x3& a, const Matrix3x2& b);	// a * b
		friend Matrix2x2 operator * (const Matrix2x3& a, const Matrix3x2& b);	// a * b
		friend Matrix3x2 operator * (const Real d, const Matrix3x2& a);			// d * a

		friend Vector2D operator * (const Vector3D& v, const Matrix3x2& m);
		friend Vector3D operator * (const Matrix3x2& m, const Vector2D& v);

		friend std::ostream& operator << (std::ostream& s, const Matrix3x2& m);					// Streamausgabe

		Vector2D& operator [] ( int i);								// Zugriff per Index
		const Vector2D& operator [] ( int i) const;
		virtual Real& operator () (int i, int j);					// Zugriff per Index
		virtual const Real& operator () (int i, int j) const;

    inline int rows () const{return 3;}
    inline int cols () const{return 2;}

		Matrix2x3 transpose () const;										// Invertiert die Matrix
	};
}

#endif


