
#include "Connector.h"
#include <math/definitions.h>

using namespace nspace;


DynamicConnector::DynamicConnector(DynamicBody & body):_body(body){
      
}

DynamicBody & DynamicConnector::body(){
  return _body;
}
const DynamicBody & DynamicConnector::body()const{
  return _body;
}

/**
  * \brief Gets the K matrix. K_{a,b} is the matrix that maps the impulse applied at point a to the impulse
  * 				result at point b of  a rigid body.  
  *
  * \return  The k matrix.
  */
void DynamicConnector::getKMatrix(Matrix3x3 & K, const Vector3D & a_wcs, const Vector3D& b_wcs) const {
  _body.calculateK(K,a_wcs,b_wcs); 
};

const Vector3D & DynamicConnector::getWorldPosition(){
  calculateWorldPosition(_worldPosition);
  return _worldPosition;
}
   
const Vector3D & DynamicConnector::getCachedWorldPosition()const{
  return _worldPosition;
}

const Vector3D & DynamicConnector::getCachedWorldVelocity()const{
  return _worldVelocity;
}

const Vector3D & DynamicConnector::getWorldVelocity(){
  calculateWorldVelocity(_worldVelocity);
  return _worldVelocity;
}

const Vector3D & DynamicConnector::getCachedWorldAcceleration()const{
  return _worldAcceleration;
}
const Vector3D & DynamicConnector::getWorldAcceleration(){
  calculateWorldAcceleration(_worldAcceleration);
  return _worldAcceleration;
}

void DynamicConnector::calculateCachedValues(){
   calculateWorldPosition(_worldPosition);
   calculateWorldVelocity(_worldVelocity);
   calculateWorldAcceleration(_worldAcceleration);
}

void DynamicConnector::addExternalForce(const Vector3D & force){
  addExternalForceToBody(force);
  _f = force;
}
