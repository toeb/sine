#include "ParticleConnector.h"
using namespace IBDS;
ParticleConnector::ParticleConnector(void)
	{
	}
	
ParticleConnector::ParticleConnector(Particle *p) {
	_particle = p;
	}


ParticleConnector::~ParticleConnector(void)
	{
	}

const Vector3D &  ParticleConnector::getPosition() const
{
	return _particle->getPosition();
}
const Vector3D & ParticleConnector::getVelocity()  const
{
	return _particle->getVelocity();
}

void ParticleConnector::addExternalForce(const Vector3D &f) {
	_particle->addExternalForce(f);
	}

const Vector3D & ParticleConnector::getNextPosition(Real h) const {
	return *(new Vector3D(_particle->getPosition() + h * _particle->getVelocity() + (h * h / 2) * _particle->getAcceleration()));
}

void ParticleConnector::applyImpulse(const Vector3D & p) {
	if (_particle->getMass() == 0) return;
	_particle->setVelocity(_particle->getVelocity() + (1 / _particle->getMass()) * p);
	}

const Matrix3x3 & ParticleConnector::getKMatrix() const {

  return _particle->calculateK(Vector3D::Zero(),Vector3D::Zero());
  /*Real m = _particle->getMass();
  if (m == 0) return Matrix3x3::Zero();
  const Matrix3x3 & E_3 = Matrix3x3::Identity();
  Matrix3x3 K = (1 / m) * E_3;

	return *(new Matrix3x3(K));*/
}

void ParticleConnector::evaluate() {
	}

void ParticleConnector::setState(const Real * state) {
	}

void ParticleConnector::getState(Real * state) const {
	}

void ParticleConnector::getDerivedState(Real * xDot)const {
	}

int ParticleConnector::getStateDimension()const {
	return 0;
}


/**
  * \brief calculates the world position.
  *
  * \return  The world position.
  */
const Vector3D &  ParticleConnector::calculateWorldPosition()const{
  return _particle->getPosition();
}

/**
  * \brief Calculates the world velocity.
  *
  * \return  The calculated world velocity.
  */
const Vector3D &  ParticleConnector::calculateWorldVelocity()const{
  return _particle->getVelocity();
}