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
const Vector3D * ParticleConnector::getVelocity() const
{
	return new Vector3D(_particle->getVelocity());
}

void ParticleConnector::addExternalForce(const Vector3D &f) {
	_particle->addExternalForce(f);
}