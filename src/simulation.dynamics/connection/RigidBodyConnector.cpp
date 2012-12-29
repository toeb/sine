#include "RigidBodyConnector.h"
using namespace nspace;
using namespace nspace::math::operators;
RigidBodyConnector::RigidBodyConnector(RigidBody & b, const Vector3D  & r)
  :DynamicConnector(b),_rigidBody(b), _r(r)
{
}
RigidBodyConnector* RigidBodyConnector::createWithWorldConnectionPoint(RigidBody & body, const Vector3D & r_wcs){
  Vector3D r_ocs;
  body.kinematics().toObjectCoordinates(r_wcs,r_ocs);
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

void RigidBodyConnector::addExternalForceToBody(const Vector3D &f) {
  _rigidBody.addExternalForce(getWorldPosition(),f);
}

void RigidBodyConnector::previewPosition(Real h,Vector3D & p_next_wcs)  {
  const Vector3D & p_wcs = getCachedWorldPosition();
  const Vector3D & v_wcs = getWorldVelocity(); // recalculates
  const Vector3D & a_wcs = getWorldAcceleration(); // recalculates acceleration
  Vector3D p = p_wcs + h*v_wcs + 0.5*h*h*a_wcs;
  p_next_wcs = p;
}

void RigidBodyConnector::applyImpulse(const Vector3D & p_wcs){
  lastImpulse += p_wcs;
  _rigidBody.applyImpulse(getCachedWorldPosition(),p_wcs);
}

void  RigidBodyConnector::calculateWorldPosition(Vector3D& p_wcs)const{
  _rigidBody.kinematics().fromObjectCoordinates(_r, p_wcs);
}

void RigidBodyConnector::calculateWorldVelocity(Vector3D & v_wcs)const{
  const Vector3D & s_wcs = _rigidBody.kinematics().position();
  /*Vector3D p_wcs;
  calculateWorldPosition(p_wcs);*/
  const Vector3D & p_wcs =getCachedWorldPosition();
  const Vector3D & v_s_wcs = _rigidBody.kinematics().velocity();
  const Vector3D & omega_wcs = _rigidBody.kinematics().angularVelocity();
  Vector3D r_wcs = p_wcs - s_wcs;
  Vector3D v = v_s_wcs + (omega_wcs ^ r_wcs); // + r' which is 0
  v_wcs =v;
}

void RigidBodyConnector::calculateWorldAcceleration(Vector3D & a_wcs)const{
  const Vector3D & s_wcs = _rigidBody.kinematics().position();
  /*Vector3D  p_wcs;
  calculateWorldPosition(p_wcs);*/
  const Vector3D & p_wcs =getCachedWorldPosition();

  const Vector3D & a_s_wcs = _rigidBody.kinematics().acceleration();
  const Vector3D & omega_wcs = _rigidBody.kinematics().angularVelocity();
  const Vector3D & omega_dot_wcs = _rigidBody.kinematics().angularAcceleration();

  Vector3D r_wcs = p_wcs - s_wcs;
  Vector3D a = a_s_wcs;
  a += (omega_wcs ^ (omega_wcs ^ r_wcs))+ (omega_dot_wcs ^r_wcs); // + values dependent on r' and r'' which are always 0
  a_wcs=a;
}