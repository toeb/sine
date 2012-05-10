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
void ParticleConnector::addExternalForce(const Vector3D &f) {
	_particle.addExternalForce(f);
}

const Vector3D & ParticleConnector::previewPosition(Real h) const {
  return _particle.previewPosition(h);
}

void ParticleConnector::applyImpulse(const Vector3D & p_wcs) {
  _particle.applyImpulse(_particle.getPosition(),p_wcs);
}



/**
  * \brief calculates the world position.
  *
  * \return  The world position.
  */
const Vector3D &  ParticleConnector::calculateWorldPosition()const{
  return _particle.getPosition();
}

/**
  * \brief Calculates the world velocity.
  *
  * \return  The calculated world velocity.
  */
const Vector3D &  ParticleConnector::calculateWorldVelocity()const{
  return _particle.getVelocity();
}