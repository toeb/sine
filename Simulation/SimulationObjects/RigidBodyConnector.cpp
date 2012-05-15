#include "RigidBodyConnector.h"
using namespace IBDS;

RigidBodyConnector::RigidBodyConnector(RigidBody & b, const Vector3D  & r)
  :Connector(b),_rigidBody(b)
{
	Quaternion q;
	Matrix3x3 R;
	q = b.getOrientation();
	q.conjugate().getMatrix3x3(R);
	_r = R * (r);
}
RigidBodyConnector* RigidBodyConnector::createWithWorldConnectionPoint(RigidBody & body, const Vector3D & r_wcs){
  Vector3D r_ocs;
  body.worldToObjectCoordinates(r_wcs,r_ocs);
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
  p_next_wcs.assign(p);
}

void RigidBodyConnector::applyImpulse(const Vector3D & p_wcs){
  _rigidBody.applyImpulse(getCachedWorldPosition(),p_wcs);
}


void  RigidBodyConnector::calculateWorldPosition(Vector3D& p_wcs)const{  
//	_rigidBody.evaluate();
  _rigidBody.objectToWorldCoordinates(_r, p_wcs);

  /*Quaternion q;
	Matrix3x3 R;
	q = _rigidBody.getOrientation();
	q.getMatrix3x3(R);

	Vector3D rnew = (R*_r);

  p_wcs.assign(_rigidBody.getPosition() + rnew);*/
}

void RigidBodyConnector::calculateWorldVelocity(Vector3D & v_wcs)const{  
  const Vector3D & s_wcs = _rigidBody.getPosition();
  /*Vector3D p_wcs;
  calculateWorldPosition(p_wcs);*/
  const Vector3D & p_wcs =getCachedWorldPosition();
  const Vector3D & v_s_wcs = _rigidBody.getVelocity();
  const Vector3D & omega_wcs = _rigidBody.getAngularVelocity();  
  Vector3D r_wcs = p_wcs - s_wcs;
  Vector3D v = v_s_wcs + (omega_wcs ^ r_wcs); // + r' which is 0
  v_wcs.assign(v);
}


void RigidBodyConnector::calculateWorldAcceleration(Vector3D & a_wcs)const{  
  const Vector3D & s_wcs = _rigidBody.getPosition();
  /*Vector3D  p_wcs;
  calculateWorldPosition(p_wcs);*/
  const Vector3D & p_wcs =getCachedWorldPosition();

  const Vector3D & a_s_wcs = _rigidBody.getAcceleration();
  const Vector3D & omega_wcs = _rigidBody.getAngularVelocity();
  const Vector3D & omega_dot_wcs = _rigidBody.getAngularAcceleration();
  
  Vector3D r_wcs = p_wcs - s_wcs;
  Vector3D a = a_s_wcs;
  a += (omega_wcs ^ (omega_wcs ^ r_wcs))+ (omega_dot_wcs ^r_wcs); // + values dependent on r' and r'' which are always 0
  a_wcs.assign(a);
}