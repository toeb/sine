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

#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "Common/Config.h"
#include "Math/Vector3D.h"

namespace IBDS
{
	class Particle
	{
	private:
		Real m_mass;
		Vector3D m_position;
		Vector3D m_velocity;
		Vector3D m_acceleration;

	public:
		Particle ();
		~Particle ();

		Real getMass() const;
		void setMass(Real val);
		IBDS::Vector3D getPosition() const;
		void setPosition(IBDS::Vector3D val);
		IBDS::Vector3D getVelocity() const;
		void setVelocity(IBDS::Vector3D val);
		IBDS::Vector3D getAcceleration() const;
		void setAcceleration(IBDS::Vector3D val);
	};
}

#endif
