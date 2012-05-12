
#include "Connector.h"
#include <Math/Matrix3x3.h>
using namespace IBDS;

Connector::Connector(Body & body):_body(body){
      
}

Body & Connector::getBody(){
  return _body;
}
const Body & Connector::getBody()const{
  return _body;
}

/**
  * \brief Gets the K matrix. K_{a,b} is the matrix that maps the impulse applied at point a to the impulse
  * 				result at point b of  a rigid body.  
  *
  * \return  The k matrix.
  */
void Connector::getKMatrix(Matrix3x3 & K, const Vector3D & a_wcs, const Vector3D& b_wcs) const {
  _body.calculateK(K,a_wcs,b_wcs); 
};

const Vector3D & Connector::getWorldPosition(){
  calculateWorldPosition(_worldPosition);
  return _worldPosition;
}
   
const Vector3D & Connector::getCachedWorldPosition()const{
  return _worldPosition;
}

const Vector3D & Connector::getCachedWorldVelocity()const{
  return _worldVelocity;
}

const Vector3D & Connector::getWorldVelocity(){
  calculateWorldVelocity(_worldVelocity);
  return _worldVelocity;
}

const Vector3D & Connector::getCachedWorldAcceleration()const{
  return _worldAcceleration;
}
const Vector3D & Connector::getWorldAcceleration(){
  calculateWorldAcceleration(_worldAcceleration);
  return _worldAcceleration;
}

void Connector::calculateCachedValues(){
   calculateWorldPosition(_worldPosition);
   calculateWorldVelocity(_worldVelocity);
   calculateWorldAcceleration(_worldAcceleration);
}

void Connector::addExternalForce(const Vector3D & force){
  addExternalForceToBody(force);
  _f= force;
}
