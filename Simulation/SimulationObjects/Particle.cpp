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

void Particle::setForce(const Vector3D & f){
  _f = f;
}
void Particle::addExternalForce(const Vector3D & f){
  _f += f;
}
void Particle::resetForce(){
  _f[0]=0;_f[1]=0;_f[2]=0;
}
const Vector3D & Particle::getForce()const{
  return _f;
}
void Particle::evaluate(){
  Real m  = getMass();
  if(m==0){
    Vector3D nullVector(0,0,0);
    setAcceleration(nullVector);
    setVelocity(nullVector);
    return;
  }
  // acceleration is force / mass
  setAcceleration(_f*(1/m));
}

void Particle::getDerivedState(Real * xDot)const{
  xDot[0]= m_velocity[0];
  xDot[1]= m_acceleration[0];
  xDot[2]= m_velocity[1];
  xDot[3]= m_acceleration[1];
  xDot[4]= m_velocity[2];
  xDot[5]= m_acceleration[2];
}
void Particle::setState(const Real * state){
  m_position[0]=state[0]; 
  m_velocity[0]=state[1];
  m_position[1]=state[2];
  m_velocity[1]=state[3];
  m_position[2]=state[4];
  m_velocity[2]=state[5];
}
 void Particle::getState(Real * state)const{
  //store the state in alternating fashion (always x_i \dot{x_i} which is needed for some integration algorithms
  state[0] = m_position[0];
  state[1] = m_velocity[0];
  state[2] = m_position[1];
  state[3] = m_velocity[1];
  state[4] = m_position[2];
  state[5] = m_velocity[2];
}
 int Particle::getStateDimension()const{
  static int dim = 6;
  return dim;
}


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

void Particle::setMass( const Real & val )
{
  m_mass = val;
}

const Vector3D & Particle::getPosition() const
{
  return m_position;
}

void IBDS::Particle::setPosition( const Vector3D & val )
{
  m_position = val;
}

const Vector3D & Particle::getVelocity() const
{
  return m_velocity;
}

void IBDS::Particle::setVelocity(const Vector3D & val )
{
  m_velocity = val;
}

const Vector3D & Particle::getAcceleration() const
{
  return m_acceleration;
}

void IBDS::Particle::setAcceleration(const Vector3D & val )
{
  m_acceleration = val;
}

void Particle::render(){
	MiniGL::drawPoint(getPosition(),5,MiniGL::darkblue);
}



const Matrix3x3 & Particle::calculateK(const Vector3D & a, const Vector3D & b)const{
  Real m = getMass();
  if (m == 0) return Matrix3x3::Zero();
  const Matrix3x3 & E_3 = Matrix3x3::Identity();
  Matrix3x3 K = (1 / m) * E_3;
	return *(new Matrix3x3(K));
}
