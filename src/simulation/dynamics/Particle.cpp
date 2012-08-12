#include "Particle.h"
#include <math/definitions.h>

using namespace nspace;

void Particle::setForce(const Vector3D & f){
  _f=f;
}
void Particle::addExternalForce(const Vector3D & f){
  _f += f;
 // _f += f;
}
void Particle::resetForce(){
  _f.setZero();
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
  MatrixOps::multiplyScalar(acceleration(),_f,1/m);
  //acceleration() = _f*(1/m);
}

void Particle::notifyStateChanged(){
//    Real * x = state().stateVector(0);
//    Real * xDot = state().stateVector(1);  
   
   position().assign(_x);
   velocity().assign(_xDot);

 }
 void Particle::notifyStateNeeded(){
//    Real * x = state().stateVector(0);
//    Real * xDot = state().stateVector(1);  
//    Real * xDotDot = state().stateVector(2);  


   position().copyTo(_x);
   velocity().copyTo(_xDot);
   acceleration().copyTo(_xDotDot);

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
    K = Matrix3x3::Zero();
    return;
  }
  const Matrix3x3 & E_3 = Matrix3x3::Identity();
  K = (1 / m) * E_3;
}
