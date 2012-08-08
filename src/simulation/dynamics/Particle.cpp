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
  acceleration() = _f*(1/m);
}

 unsigned int Particle::stateDimension()const{return 3;}
 unsigned int Particle::availableDerivatives()const{return 2;}
 void Particle::importState(const IState & x){
   const Real * data = x.data(0);
   const Real * dataDeriv = x.data(1);
   position().assign(data);
   velocity().assign(dataDeriv);/*
   position()(0)=x(0,0);
   position()(1)=x(1,0);
   position()(2)=x(2,0);
   velocity()(0)=x(0,1);
   velocity()(1)=x(1,1);
   velocity()(2)=x(2,1);*/

 }
 void Particle::exportState(IState & x)const{
   Real * data = x.data(0);
   Real * dataDeriv = x.data(1);
   position().copyTo(data);
   velocity().copyTo(dataDeriv);
   /*x(0,0)=position()(0);
   x(1,0)=position()(1);
   x(2,0)=position()(2);
   x(0,1)=velocity()(0);
   x(1,1)=velocity()(1);
   x(2,1)=velocity()(2);*/
 }
 void Particle::exportDerivedState(IState & xDot)const{
   Real * data = xDot.data(0);
 Real * dataDeriv = xDot.data(1);
 velocity().copyTo(data);
 acceleration().copyTo(dataDeriv);
   /*xDot(0,0)=velocity()(0);
   xDot(1,0)=velocity()(1);
   xDot(2,0)=velocity()(2);
   xDot(0,1)=acceleration()(0);
   xDot(1,1)=acceleration()(1);
   xDot(2,1)=acceleration()(2);*/
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
