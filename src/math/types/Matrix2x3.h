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

#ifndef __MATRIX2X3_H__
#define __MATRIX2X3_H__

#include "Common/Config.h"
#include "Matrix.h"
#include "Vector2D.h"
#include "Matrix3x3.h"

namespace nspace
{
	class Matrix3x2;

	/** Matrix2x3 ist eine Klasse für Berechnungen mit einer 2x3 Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Matrix2x3 : public Matrix
	{
	public:
		/** Zeilenvektoren der 2x3 Matrix */
		Vector3D v[2];

	public:
		Matrix2x3();
		Matrix2x3(const Vector3D& v0, const Vector3D &v1);

		friend Matrix2x3 operator - (const Matrix2x3& a);						// -m1
		friend Matrix2x3 operator + (const Matrix2x3& a, const Matrix2x3& b);	// m1 + m2
		friend Matrix2x3 operator - (const Matrix2x3& a, const Matrix2x3& b);	// m1 - m2
		friend Matrix2x3 operator * (const Matrix2x2& a, const Matrix2x3& b);	// a * b
		friend Matrix2x3 operator * (const Matrix2x3& a, const Matrix3x3& b);	// a * b
		friend Matrix2x3 operator * (const Real d, const Matrix2x3& a);		// d * a

		friend Vector3D operator * (const Vector2D& v, const Matrix2x3& m);
		friend Vector2D operator * (const Matrix2x3& m, const Vector3D& v);

		Vector3D& operator [] ( int i);							// Zugriff per Index
		const Vector3D& operator [] ( int i) const;
		virtual Real& operator () (int i, int j);				// Zugriff per Index
		virtual const Real& operator () (int i, int j) const;

    inline int rows () const{return 2;}
    inline int cols () const{return 3;}

		friend std::ostream& operator << (std::ostream& s, const Matrix2x3& m);		// Streamausgabe

		Matrix3x2 transpose() const;										// Transponiert die 3x3-Matrix
	};
}

#endif


