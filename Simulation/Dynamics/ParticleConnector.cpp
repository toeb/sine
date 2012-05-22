#include "ParticleConnector.h"
using namespace IBDS;

ParticleConnector::ParticleConnector(Particle & p):Connector(p), _particle(p) {
}

ParticleConnector::~ParticleConnector(void)
{
}

const Vector3D &  ParticleConnector::getObjectCoordinatePosition() const
{
  return Vector3D::Zero();
}
void ParticleConnector::addExternalForceToBody(const Vector3D &f) {
	_particle.addExternalForce(f);
}

void ParticleConnector::previewPosition(Real h, Vector3D & p_next_wcs)  {
  _particle.previewPosition(h,p_next_wcs);
}

void ParticleConnector::applyImpulse(const Vector3D & p_wcs) {
  _particle.applyImpulse(_particle.getPosition(),p_wcs);
}



/**
  * \brief calculates the world position.
  *
  * \return  The world position.
  */
void  ParticleConnector::calculateWorldPosition(Vector3D & p_wcs)const{
  p_wcs .assign( _particle.getPosition());
}

/**
  * \brief Calculates the world velocity.
  *
  * \return  The calculated world velocity.
  */
void  ParticleConnector::calculateWorldVelocity(Vector3D & v_wcs)const{
  v_wcs.assign( _particle.getVelocity());
}

void ParticleConnector::calculateWorldAcceleration(Vector3D & a_wcs)const{
  a_wcs.assign( _particle.getAcceleration());
}

void ParticleConnector::setWorldPosition(Vector3D &position) {
	_particle.setPosition(position);
	calculateWorldPosition(_worldPosition);	// updated cached value
}
