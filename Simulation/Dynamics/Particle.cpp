#include "Particle.h"
#include <Math/Matrix3x3.h>

using namespace IBDS;

void Particle::setForce(const Vector3D & f){
  _f.assign( f);
}
void Particle::addExternalForce(const Vector3D & f){
  Vector3D::add(_f,f,_f);
 // _f += f;
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

const Vector3D & Particle::getAcceleration()const{
  return _acceleration;
}


void Particle::getDerivedState(Real * xDot)const{
  _velocity.copyTo(&(xDot[0]));
  _acceleration.copyTo(&(xDot[3]));
}
void Particle::setState(const Real * state){
  _position.assign(&(state[0]));
  _velocity.assign(&(state[3]));
}
 void Particle::getState(Real * state)const{
   _position.copyTo(&(state[0]));
   _velocity.copyTo(&(state[3]));
}
 int Particle::getStateDimension()const{
  static int dim = 6;
  return dim;
}


Particle::Particle () 
{
  setMass(1.0);
 _position = Vector3D(0,0,0);
 _velocity = Vector3D(0,0,0);
 _acceleration = Vector3D(0,0,0);
}

Particle::~Particle () 
{	
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
