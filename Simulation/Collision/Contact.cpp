#pragma once
#include <Simulation\Collision\Contact.h>

using namespace IBDS;

void Contact::getRelativeVelocityVector (Vector3D & out) {
	if (!_c1 || !_c2) {
		out = Vector3D::Zero();
		return;
		}

	_c1->calculateCachedValues();
	_c2->calculateCachedValues();
	const Vector3D &v1 = _c1->getWorldVelocity();
	const Vector3D &v2 = _c2->getWorldVelocity();

	Vector3D::subtract(v2, v1, out);
	}


Contact::Contact(DynamicBody &body1, DynamicBody &body2, const Vector3D &pA_wcs_in, const Vector3D &pB_wcs_in, const Vector3D &normal_in, Real penetrationDepth_in)
	: pA_wcs(pA_wcs_in), pB_wcs(pB_wcs_in), normal(normal_in), penetrationDepth(penetrationDepth_in) {

		_c1 = 0;
		_c2 = 0;

		RigidBody *rigidBody1 = dynamic_cast<RigidBody*>(&body1);
		if (rigidBody1) {
			_c1 = RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody1,pA_wcs);
			}
		else {
			Particle *particle1 = dynamic_cast<Particle*>(&body1);
			if (particle1) {
				_c1 = new ParticleConnector(*particle1);
				}
			}

		RigidBody *rigidBody2 = dynamic_cast<RigidBody*>(&body2);
		if (rigidBody2) {
			_c2 = RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody2,pB_wcs);
			}
		else {
			Particle *particle2 = dynamic_cast<Particle*>(&body2);
			if (particle2) {
				_c2 = new ParticleConnector(*particle2);
				}
			}
	}

void Contact::getNormalRelativeVelocity(Real &out) {
	Vector3D v_rel;
	getRelativeVelocityVector(v_rel);
	Vector3D::dotProduct(v_rel, normal, out);
	}

void Contact::getNormalRelativeVelocityVector (Vector3D &out) {
	Real v;
	getNormalRelativeVelocity(v);
	Vector3D::multiplyScalar(v,normal,out);
	}

ContactType Contact::classify() {
	if (!_c1 || !_c2) return UNKNOWN;

	Real v_rel_n;
	getNormalRelativeVelocity(v_rel_n);

	double threshold = 0.06;//*10e-5;
	if (v_rel_n >= threshold)
		return DRIFTING_APART;
	else if (v_rel_n > -threshold)
		return RESTING_CONTACT;
	else
		return COLLISION;
	}

Connector* Contact::getConnector1 () {
	return _c1;
	}

Connector* Contact::getConnector2 () {
	return _c2;
	}