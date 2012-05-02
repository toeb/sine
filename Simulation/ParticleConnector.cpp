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

const Vector3D * ParticleConnector::getPosition() const
{
	return new Vector3D(_particle->getPosition());
}
const Vector3D * ParticleConnector::getVelocity() 
{
	return new Vector3D(_particle->getVelocity());
}

void ParticleConnector::addExternalForce(const Vector3D &f) {
	_particle->addExternalForce(f);
	}

const Vector3D * ParticleConnector::getNextPosition(Real h) const {
	return new Vector3D(_particle->getPosition() + h * _particle->getVelocity() + (h * h / 2) * _particle->getAcceleration());
}

void ParticleConnector::applyImpulse(Vector3D const * const p) {
	if (_particle->getMass() == 0) return;
	_particle->setVelocity(_particle->getVelocity() + (1 / _particle->getMass()) * *p);
	}

Matrix3x3 const * const ParticleConnector::getKMatrix() const {
	if (_particle->getMass() == 0) return new Matrix3x3(Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0));
	Matrix3x3 idMatrix;
	return new Matrix3x3((1 / _particle->getMass()) * idMatrix);
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
