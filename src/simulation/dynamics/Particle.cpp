#include "Particle.h"
#include <Math/Matrix3x3.h>

using namespace IBDS;
const TypeId Particle::type ="Particle";
const TypeId Particle::getBodyType()const{
  return type;
}
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
    acceleration() = Vector3D::Zero();
    velocity().setZero();
    return;
  }
  // acceleration is force / mass
  acceleration() = _f*(1/m);
}




void Particle::getDerivedState(Real * xDot)const{
  velocity().copyTo(&(xDot[0]));
  acceleration().copyTo(&(xDot[3]));
}
void Particle::setState(const Real * state){
  position().assign(&(state[0]));
  velocity().assign(&(state[3]));
}
 void Particle::getState(Real * state)const{
   position().copyTo(&(state[0]));
   velocity().copyTo(&(state[3]));
}
 int Particle::getStateDimension()const{
  static int dim = 6;
  return dim;
}






 void Particle::applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs){
   Real m = getMass();
   if(m==0)return;
   Vector3D vDelta = 1/m*p_wcs;
   velocity() += vDelta;
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
