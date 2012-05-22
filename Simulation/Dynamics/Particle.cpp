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
#include <Math/Matrix3x3.h>

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
void Particle::calculateDynamics(){
  Real m  = getMass();
  if(m==0){
    _acceleration = Vector3D::Zero();
    setVelocity(Vector3D::Zero());
    return;
  }
  // acceleration is force / mass
  _acceleration = _f*(1/m);
}



void Particle::getDerivedState(Real * xDot)const{
  xDot[0]= _velocity[0];
  xDot[1]= _acceleration[0];
  xDot[2]= _velocity[1];
  xDot[3]= _acceleration[1];
  xDot[4]= _velocity[2];
  xDot[5]= _acceleration[2];
}
void Particle::setState(const Real * state){
  _position[0]=state[0]; 
  _velocity[0]=state[1];
  _position[1]=state[2];
  _velocity[1]=state[3];
  _position[2]=state[4];
  _velocity[2]=state[5];
}
 void Particle::getState(Real * state)const{
  //store the state in alternating fashion (always x_i \dot{x_i} which is needed for some integration algorithms
  state[0] =_position[0];
  state[1] =_velocity[0];
  state[2] =_position[1];
  state[3] =_velocity[1];
  state[4] =_position[2];
  state[5] =_velocity[2];
}
 int Particle::getStateDimension()const{
  static int dim = 6;
  return dim;
}


Particle::Particle () 
{
 _mass = 1.0;
 _position = Vector3D(0,0,0);
 _velocity = Vector3D(0,0,0);
 _acceleration = Vector3D(0,0,0);
}

Particle::~Particle () 
{	
}

Real IBDS::Particle::getMass() const
{
  return _mass;
}

void Particle::setMass( const Real & val )
{
  _mass = val;
}

const Vector3D & Particle::getPosition() const
{
  return _position;
}

void IBDS::Particle::setPosition( const Vector3D & val )
{
  _position = val;
}

const Vector3D & Particle::getVelocity() const
{
  return _velocity;
}

void IBDS::Particle::setVelocity(const Vector3D & val )
{
  _velocity = val;
}



 void Particle::applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs){
   Real m = getMass();
   if(m==0)return;
   Vector3D vDelta = 1/m*p_wcs;
   _velocity += vDelta;
 }

void Particle::calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const{
  Real m = getMass();
  if (m == 0){
    K.assign(Matrix3x3::Zero());
    return;
  }
  const Matrix3x3 & E_3 = Matrix3x3::Identity();
  K.assign((1 / m) * E_3);
}
