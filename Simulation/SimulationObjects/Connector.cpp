
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
  * \brief Gets the k matrix. K_{a,b} is the matrix that maps the impulse applied at point a to the impulse
  * 				result at point b of  a rigid body.  
  *
  * \return  The k matrix.
  */
void Connector::getKMatrix(Matrix3x3 & K) const {
  const Vector3D & a_wcs = getWorldPosition();
  _body.calculateK(K,a_wcs,a_wcs); 
};

   
const Vector3D & Connector::getWorldPosition()const{
/* return calculateWorldPosition();//*/
  return _worldPosition;
}


void Connector::calculateCachedValues(){
   calculateWorldPosition(_worldPosition);
}

void Connector::addExternalForce(const Vector3D & force){
  addExternalForceToBody(force);
  _f= force;
}
