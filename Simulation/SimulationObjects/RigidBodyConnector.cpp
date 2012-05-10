#include "RigidBodyConnector.h"
using namespace IBDS;

RigidBodyConnector::RigidBodyConnector(RigidBody & b, const Vector3D  & r)
  :Connector(b),_rigidBody(b), _r(r)
{
}
RigidBodyConnector* RigidBodyConnector::createWithWorldConnectionPoint(RigidBody & body, const Vector3D & r_wcs){
  Vector3D & r_ocs = body.worldToObjectCoordinates(r_wcs);
  return RigidBodyConnector::createWithLocalConnectionPoint(body,r_ocs);
}
RigidBodyConnector* RigidBodyConnector::createWithLocalConnectionPoint(RigidBody & body, const Vector3D & r_ocs){
  return new RigidBodyConnector(body,r_ocs);
}
RigidBodyConnector::~RigidBodyConnector(void)
{
}

const Vector3D &  RigidBodyConnector::getObjectCoordinatePosition() const {
	return _r;
}



void RigidBodyConnector::addExternalForce(const Vector3D &f) {
  _rigidBody.addExternalForce(getWorldPosition(),f);
}

const Vector3D & RigidBodyConnector::previewPosition(Real h) const {
  const Vector3D & r_wcs = getWorldPosition();
  const Vector3D & v_wcs = getWorldVelocity();  
  
  Vector3D r_next_wcs = r_wcs + h*v_wcs;
  return r_next_wcs.copy();
}

void RigidBodyConnector::applyImpulse(const Vector3D & p_wcs){
  _rigidBody.applyImpulse(getWorldPosition(),p_wcs);
}


const Vector3D &  RigidBodyConnector::calculateWorldPosition()const{
   return _rigidBody.objectToWorldCoordinates(_r);
}

const Vector3D & RigidBodyConnector::calculateWorldVelocity()const{
  const Vector3D & v_s_wcs = _rigidBody.getVelocity();
  const Vector3D & omega_wcs = _rigidBody.getAngularVelocity();
  const Vector3D & r_wcs = calculateWorldPosition();  
  const Vector3D & r_s_wcs = _rigidBody.getPosition();
  Vector3D r = r_wcs - r_s_wcs;
  Vector3D v = v_s_wcs +( omega_wcs ^ r);
  return v.copy();
}