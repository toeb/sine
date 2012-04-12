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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Common/Config.h"
#include "Matrix.h"

namespace IBDS
{
	/** Vector ist die Oberklasse aller Vektorklassen
	  \author Jan Bender
	  */
	class Vector : public Matrix
	{
	public:
		virtual Real& operator [] (int i) = 0;				// Zugriff per Index
		virtual const Real& operator [] (int i) const = 0;

		virtual Real length() const = 0;			    // L�nge
		virtual Real length2() const = 0;			    // Quadratische L�nge
		virtual void normalize() = 0;				// Normierung 

	};
}

#endif

