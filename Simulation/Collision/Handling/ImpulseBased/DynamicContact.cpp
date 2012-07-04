#pragma once
#include "DynamicContact.h"
#include <Simulation/Dynamics/Connection/ConnectorFactory.h>

using namespace IBDS;
using namespace std;

void DynamicContact::getRelativeVelocityVector (Vector3D & out) {
	/*if (!_c1 || !_c2) {
		out = Vector3D::Zero();
		return;
		}*/

	connectorA().calculateCachedValues();
	connectorB().calculateCachedValues();
	const Vector3D &v1 = connectorA().getWorldVelocity();
	const Vector3D &v2 = connectorB().getWorldVelocity();
  Vector3D::subtract(v2, v1, out);
}

DynamicContact::~DynamicContact(){
  ConnectorFactory::instance().freeConnector(_cA);
  ConnectorFactory::instance().freeConnector(_cB);
  _cA = 0;
  _cB = 0;
}

DynamicContact::DynamicContact( DynamicCollidable &collidableA, 
      DynamicCollidable &collidableB, Contact &contact): 
  _contact(contact), 
  _collidableA(collidableA), 
  _collidableB(collidableB),
  _cA(0),
  _cB(0) 
{
  _cA = ConnectorFactory::instance().createWithWorldConnectionPoint(collidableA.dynamicBody(),contact.pA_wcs);
  _cB = ConnectorFactory::instance().createWithWorldConnectionPoint(collidableB.dynamicBody(),contact.pB_wcs);

  if(!(_cA&&_cB)){
    cout << "Dynamic Contact could not create Connectors for contact!!!"<<endl;
  }
	
}

void DynamicContact::getNormalRelativeVelocity(Real &out) {
  Vector3D v_rel;
  getRelativeVelocityVector(v_rel);
  Vector3D::dotProduct(v_rel, contact().normal, out);
}

void DynamicContact::getNormalRelativeVelocityVector (Vector3D &out) {
	Real v;
	getNormalRelativeVelocity(v);
	Vector3D::multiplyScalar(v,contact().normal,out);
}

ContactType DynamicContact::classify() {
//if (!_cA || !_cB) return UNKNOWN;
  Real v_rel_n;
  getNormalRelativeVelocity(v_rel_n);

  Real tolerance = 10e-3;
  Real gravity = 9.81;
  Real threshold = sqrt(2*gravity*tolerance);

  if (v_rel_n >= threshold)
	  return DRIFTING_APART;
  else if (v_rel_n > -threshold)
	  return RESTING_CONTACT;
  else
	  return COLLISION;
}


void DynamicContact::applyNormalImpulse(Vector3D &p) {
	//if (!_c1 || !_c2) return;
	Vector3D newAccumulatedImpulse = _accumulatedImpulse + p;
	Real dotProduct;
	Vector3D::dotProduct(newAccumulatedImpulse, contact().normal, dotProduct);

	if (dotProduct <= 0) {
    connectorA().applyImpulse(p);
		connectorB().applyImpulse(-p);
		Vector3D::add(_accumulatedImpulse, p, _accumulatedImpulse); 
	}

	// anti-sticking:
	else {
		connectorA().applyImpulse(-_accumulatedImpulse);
		connectorB().applyImpulse(_accumulatedImpulse);
		_accumulatedImpulse.setZero();
	}
}

void DynamicContact::applyTangentialImpulse(Vector3D &p) {
	connectorA().applyImpulse(p);
  connectorB().applyImpulse(-p);
}

