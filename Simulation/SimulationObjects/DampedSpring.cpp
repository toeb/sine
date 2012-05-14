#include "DampedSpring.h"
using namespace IBDS;

DampedSpring::~DampedSpring()
{
}

DampedSpring::DampedSpring(Connector &cA, Connector &cB, Real k_s, Real k_d, Real restLength) :
  _cA(cA),_cB(cB){
	_k_s = k_s;
	_k_d = k_d;
	_l0 = restLength;
}

void DampedSpring::act (std::vector<Body*> & target, Real time) {
  Vector3D f;
  calculateSpringForce(f);
	_cA.addExternalForce(f);
	_cB.addExternalForce(-f);
}
inline void DampedSpring::calculateSpringAndDampeningForce(Vector3D & f_s_wcs,Vector3D & f_d_wcs)const{  
  const Vector3D & a_wcs = _cA.getCachedWorldPosition();
  const Vector3D & b_wcs = _cB.getCachedWorldPosition();

  Vector3D v_a_wcs,v_b_wcs;  
  _cA.calculateWorldVelocity(v_a_wcs);
  _cB.calculateWorldVelocity(v_b_wcs);

	Vector3D n_wcs;	
  
	n_wcs = b_wcs - a_wcs;
	Real amount = n_wcs.length();
  
  n_wcs = (1/amount)*n_wcs;

  Vector3D deltaV = v_b_wcs-v_a_wcs;
  //if spring force is 0 reuturn 0
  if(amount ==0){
    f_s_wcs.assign(Vector3D::Zero());
    f_d_wcs.assign(Vector3D::Zero());//this is wrong i the zero point.
  }else{
    f_s_wcs.assign( _k_s * (amount - _l0) *n_wcs);
    // 
     f_d_wcs.assign( (_k_d * (v_b_wcs - v_a_wcs) * n_wcs) * n_wcs );
  }
}

inline void DampedSpring::calculateSpringForce(Vector3D & f_wcs)const{
  Vector3D  f_s_wcs,f_d_wcs;
  calculateSpringAndDampeningForce(f_s_wcs,f_d_wcs);
  f_wcs.assign(f_s_wcs+f_d_wcs);
}
Real DampedSpring::getStiffnessConstant()const{
  return _k_s;
}
Real DampedSpring:: getDampeningConstant()const{
  return _k_d;
}
const Connector & DampedSpring::getConnectorA()const{
  return _cA;
}
const Connector& DampedSpring::getConnectorB()const{
  return _cB;
}