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

#ifndef __MATRIX3X3_H__
#define __MATRIX3X3_H__

#include "Common/Config.h"
#include "Matrix.h"
#include "Vector3D.h"

namespace IBDS
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
    Matrix3x3(const Matrix3x3 & rhs);
		Matrix3x3();
		Matrix3x3(const Vector3D &v0, const Vector3D &v1, const Vector3D &v2);
    ~Matrix3x3();

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


