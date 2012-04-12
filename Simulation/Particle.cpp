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

#include "Particle.h"

using namespace IBDS;

Particle::Particle () 
{
	m_mass = 1.0;
	m_position = Vector3D(0,0,0);
	m_velocity = Vector3D(0,0,0);
	m_acceleration = Vector3D(0,0,0);
}

Particle::~Particle () 
{	
}

Real IBDS::Particle::getMass() const
{
	return m_mass;
}

void IBDS::Particle::setMass( Real val )
{
	m_mass = val;
}

IBDS::Vector3D IBDS::Particle::getPosition() const
{
	return m_position;
}

void IBDS::Particle::setPosition( IBDS::Vector3D val )
{
	m_position = val;
}

IBDS::Vector3D IBDS::Particle::getVelocity() const
{
	return m_velocity;
}

void IBDS::Particle::setVelocity( IBDS::Vector3D val )
{
	m_velocity = val;
}

IBDS::Vector3D IBDS::Particle::getAcceleration() const
{
	return m_acceleration;
}

void IBDS::Particle::setAcceleration( IBDS::Vector3D val )
{
	m_acceleration = val;
}
