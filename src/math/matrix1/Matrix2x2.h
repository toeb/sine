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

#ifndef __MATRIX2X2_H__
#define __MATRIX2X2_H__

#include <common/Config.h>
#include <math/Matrix.h>
#include "Vector2D.h"
#include "Matrix3x3.h"

namespace nspace{
	class Matrix3x2;
	class Matrix2x3;


	/** Matrix2x2 ist eine Klasse für Berechnungen mit einer 2x2 Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Matrix2x2 : public nspace::Matrix<Real>
	{
	public:
		/** Zeilenvektoren der 2x2 Matrix */
		Vector2D v[2];

	public:
		Matrix2x2();
		Matrix2x2(const Vector2D& v0, const Vector2D &v1);
		Matrix2x2 (const Matrix3x3& m);

		friend Matrix2x2 operator - (const Matrix2x2& a);						// -m1
		friend Matrix2x2 operator + (const Matrix2x2& a, const Matrix2x2& b);	// m1 + m2
		friend Matrix2x2 operator - (const Matrix2x2& a, const Matrix2x2& b);	// m1 - m2
		friend Matrix2x2 operator * (const Matrix2x2& a, const Matrix2x2& b);	// a * b
		friend Matrix2x2 operator * (const Matrix2x3& a, const Matrix3x2& b);	// a * b
		friend Matrix2x2 operator * (const Real d, const Matrix2x2& a);		// d * a

		friend Vector2D operator * (const Vector2D& v, const Matrix2x2& m);

		Vector2D& operator [] ( int i);								// Zugriff per Index
		const Vector2D& operator [] ( int i) const;
        virtual const Real& operator () (int i, int j) const;
		virtual Real& operator () (int i, int j);					// Zugriff per Index

		friend std::ostream& operator << (std::ostream& s, const Matrix2x2& m);		// Streamausgabe

		inline int rows () const{return 2;}
    inline int cols () const{return 2;}

		Matrix2x2 transpose() const;								// Transponiert die 3x3-Matrix
		Matrix2x2 inverse () const;								// Invertiert die Matrix
	};
}
#endif



