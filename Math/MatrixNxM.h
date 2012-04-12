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

#ifndef __MATRIXNXM_H__
#define __MATRIXNXM_H__

#include "Common/Config.h"
#include "Matrix.h"
#include "VectorND.h"

namespace IBDS
{
	/** MatrixNxM ist eine Klasse für Berechnungen mit einer nxm Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class MatrixNxM : public Matrix
	{
	public:
		/** Zeilenvektoren der 2x2 Matrix */
		VectorND v[6];
		/* Anzahl Zeilen */
		int rows;
		/* Anzahl Spalten */
		int cols;


	public:
		MatrixNxM(const int rows, const int cols);
		MatrixNxM (const MatrixNxM& copy);
		~MatrixNxM();

		friend MatrixNxM operator - (const MatrixNxM& a);						// -m1
		friend MatrixNxM operator + (const MatrixNxM& a, const MatrixNxM& b);	// m1 + m2
		friend MatrixNxM operator - (const MatrixNxM& a, const MatrixNxM& b);	// m1 - m2
		friend MatrixNxM operator * (const MatrixNxM& a, const MatrixNxM& b);	// a * b
		friend MatrixNxM operator * (const Real d, const MatrixNxM& a);		// d * a
		MatrixNxM& operator = (const MatrixNxM& m);

		friend VectorND operator * (const VectorND& v, const MatrixNxM& m);

		VectorND& operator [] ( int i);							// Zugriff per Index
		const VectorND& operator [] ( int i) const;
		virtual Real& operator () (int i, int j);				// Zugriff per Index
		virtual const Real& operator () (int i, int j) const;

		friend std::ostream& operator << (std::ostream& s, const MatrixNxM& m);	// Streamausgabe

		virtual int getRows () const;
		virtual int getCols () const;

		MatrixNxM transpose() const;									// Transponiert die 3x3-Matrix
		void zero ();
		bool inverse ();

		friend class VectorND;
	};
}

#endif


