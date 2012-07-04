#include "ParticleConnector.h"
using namespace IBDS;

ParticleConnector::ParticleConnector(Particle & p):Connector(p), _particle(p){

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
  const Vector3D & s_wcs = _particle.position();
  const Vector3D & v_wcs = _particle.velocity();
  const Vector3D & a_wcs = _particle.acceleration();
  Vector3D s_preview = s_wcs + h*v_wcs+ 0.5*h*h*a_wcs;
  p_next_wcs.assign(s_preview);
}

void ParticleConnector::applyImpulse(const Vector3D & p_wcs) {
  _particle.applyImpulse(_particle.position(),p_wcs);
}



/**
  * \brief calculates the world position.
  *
  * \return  The world position.
  */
void  ParticleConnector::calculateWorldPosition(Vector3D & p_wcs)const{
  p_wcs .assign( _particle.position());
}

/**
  * \brief Calculates the world velocity.
  *
  * \return  The calculated world velocity.
  */
void  ParticleConnector::calculateWorldVelocity(Vector3D & v_wcs)const{
  v_wcs.assign( _particle.velocity());
}

void ParticleConnector::calculateWorldAcceleration(Vector3D & a_wcs)const{
  a_wcs.assign( _particle.velocity());
}

void ParticleConnector::setWorldPosition(Vector3D &p) {
	_particle.position() = p;
	calculateWorldPosition(_worldPosition);	// updated cached value
}
