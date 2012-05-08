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

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Common/Config.h"
#include "Vector3D.h"
#include "Matrix3x3.h"

namespace IBDS
{
	/** Quaternion ist eine Klasse für Berechnungen mit einem Quaternion, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class Quaternion
	{
	public:
		/** w-Komponente des Quaternions */
		Real w;
		/** x-Komponente des Quaternions */
		Real x;
		/** y-Komponente des Quaternions */
		Real y;
		/** z-Komponente des Quaternions */
		Real z;

	public:
		Quaternion();
		Quaternion(const Real pw, const Real px, const Real py, const Real pz);
		void setFromAxisAngle (const Vector3D &axis, const Real angle);
		void getAxisAngle (Vector3D &axis, Real &angle);
		void setFromMatrix3x3 (Matrix3x3 *m);
		void getMatrix3x3 (Matrix3x3 &m)const;
		void setFromMatrix3x3T (Matrix3x3 *m);
		void getMatrix3x3T (Matrix3x3 &m)const;
		void normalize ();
		Real length ();
		Real length2 ();
		Quaternion conjugate ();

		friend Quaternion operator - (const Quaternion& a);							// -m1
		friend Quaternion operator + (const Quaternion& a, const Quaternion& b);	// m1 + m2
		friend Quaternion operator - (const Quaternion& a, const Quaternion& b);	// m1 - m2
		friend Quaternion operator * (const Quaternion& a, const Quaternion& b);	// a * b
		friend Quaternion operator * (const Real d, const Quaternion& a);			// d * a
		friend Quaternion operator | (const Vector3D& a, const Quaternion& b);		// (0,a^T) * b
		friend Quaternion operator | (const Quaternion& a, const Vector3D& b);		// a * (0,b^T)
		Quaternion& operator = (const Quaternion& q);								// Zuweisung
		FORCE_INLINE Real& Quaternion::operator [] (const int i)
		{
			switch(i)
			{
				case 0: return w;
				case 1: return x;
				case 2: return y;
				case 3: return z;
			}
			return w;
		}

		FORCE_INLINE const Real& Quaternion::operator [] (const int i) const
		{
			switch(i)
			{
				case 0: return w;
				case 1: return x;
				case 2: return y;
				case 3: return z;
			}
			return w;
		}

		friend std::ostream& operator << (std::ostream& s, Quaternion& q);					// Streamausgabe
	};
}

#endif

