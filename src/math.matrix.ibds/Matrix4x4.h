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
#include <math.matrix/Matrix.h>
#include "Vector3D.h"
#include "Matrix3x3.h"

namespace nspace{

	/** Matrix4x4 ist eine Klasse für Berechnungen mit einer 4x4 Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Matrix4x4 : public nspace::Matrix<Real>
	{
	public:
		/** Zeilenvektoren der 4x4 Matrix */
		Real m[4][4]; 

	public:
		Matrix4x4();
		Matrix4x4(Real matrix[4][4]);
    
		friend Matrix4x4 operator - (const Matrix4x4& a);						// -m1
		friend Matrix4x4 operator + (const Matrix4x4& a, const Matrix4x4& b);	// m1 + m2
		friend Matrix4x4 operator - (const Matrix4x4& a, const Matrix4x4& b);	// m1 - m2
		friend Matrix4x4 operator * (const Matrix4x4& a, const Matrix4x4& b);	// a * b
		friend Matrix4x4 operator ^ (const Matrix4x4& a, const Matrix4x4& b);	// a ^ b
		friend Matrix4x4 operator * (const Real d, const Matrix4x4& a);		// d * a
		friend Vector3D operator * (const Matrix4x4& a, const Vector3D &v);		// m * v (Vektor)
		friend Vector3D operator ^ (const Matrix4x4& a, const Vector3D &v);		// m * p (Punkt)
		Matrix4x4& operator = ( const Matrix4x4& m );							// Zuweisung

		friend std::ostream& operator << (std::ostream& s, const Matrix4x4& m);	// Streamausgabe
		virtual Real& operator () (int i, int j);				// Zugriff per Index
		const virtual Real& operator () (int i, int j) const;

		inline int rows () const{return 4;}
		inline int cols () const{return 4;}

		Matrix4x4 transpose() const;									// Transponiert die 3x3-Matrix
		Matrix4x4 inverse () const;
		void getTransformation (Vector3D &translation, Matrix3x3 &rotation, Vector3D &scale) const;
		void set(const Real matrix[16]);
		void get(Real *matrix);
		void setTransformation (const Vector3D &translation, const Matrix3x3 &rotation, const Vector3D &scale);
	};
}

