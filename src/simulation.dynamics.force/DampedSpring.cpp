#include "DampedSpring.h"
using namespace nspace;


const Vector3D & DampedSpring::getForce()const{
  return _f_wcs;
}
const Vector3D & DampedSpring::getSpringForce()const{
  return _f_s_wcs;
}
const Vector3D & DampedSpring::getDampeningForce()const{
  return _f_d_wcs;
}

DampedSpring::~DampedSpring()
{
}

DampedSpring::DampedSpring(DynamicConnector &cA, DynamicConnector &cB, Real k_s, Real k_d, Real restLength) :
  _cA(cA),_cB(cB){
	_k_s = k_s;
	_k_d = k_d;
  _lastLength  =_currentLength=restLength;
	_l0 = restLength;
}

void DampedSpring::act (std::vector<DynamicBody*> & target, Real time) {
  calculateSpringAndDampeningForce();
	_cA.addExternalForce(_f_wcs);
	_cB.addExternalForce(-_f_wcs);
}
inline void DampedSpring::calculateSpringAndDampeningForce(){  
  _lastLength = _currentLength;

   //_cA.calculateCachedValues();
   //_cB.calculateCachedValues();
  const Vector3D & a_wcs = _cA.getCachedWorldPosition();
  const Vector3D & b_wcs = _cB.getCachedWorldPosition();
  Vector3D v_a_wcs,v_b_wcs;  
  _cA.calculateWorldVelocity(v_a_wcs);
  _cB.calculateWorldVelocity(v_b_wcs);

	Vector3D n_wcs;	
//  Vector3D::subtract(b_wcs,a_wcs,n_wcs);
	n_wcs=b_wcs-a_wcs;
  //n_wcs = b_wcs - a_wcs;
	_currentLength = n_wcs.norm();
  //Vector3D::multiplyScalar(1/_currentLength,n_wcs,n_wcs);
  n_wcs /= _currentLength;
  //n_wcs = (1/amount)*n_wcs;
  Vector3D deltaV;
  //Vector3D::subtract(v_b_wcs,v_a_wcs,deltaV);
  deltaV = v_b_wcs-v_a_wcs;
  //Vector3D deltaV = v_b_wcs-v_a_wcs;
  //if spring force is 0 reuturn 0
  if(_currentLength ==0){
    _f_s_wcs=Vector3D::Zero();
    _f_d_wcs=Vector3D::Zero();//this is wrong. 
  }else{
    //Vector3D::multiplyScalar( _k_s * (_currentLength - _l0), n_wcs,_f_s_wcs);
    _f_s_wcs = (_k_s*(_currentLength-_l0))*n_wcs;
    //f_s_wcs.assign( _k_s * (amount - _l0) *n_wcs);
    Real velocityDotNormal;
    matrix::innerProduct(velocityDotNormal,deltaV,n_wcs);
    //velocityDotNormal = deltaV * n_wcs;
    //Vector3D::dotProduct(deltaV,n_wcs,velocityDotNormal);
    _f_d_wcs = (_k_d*velocityDotNormal)*n_wcs;
    //Vector3D::multiplyScalar( _k_d*velocityDotNormal,n_wcs,_f_d_wcs);
    // f_d_wcs.assign( (_k_d * (deltaV * n_wcs)) * n_wcs );
  }
  //Vector3D::add(_f_s_wcs,_f_d_wcs,_f_wcs);
  _f_wcs=_f_s_wcs+_f_d_wcs;
  //f_wcs = f_s_wcs+f_d_wcs
}

Real DampedSpring::getStiffnessConstant()const{
  return _k_s;
}
Real DampedSpring:: getDampeningConstant()const{
  return _k_d;
}
void DampedSpring::setDampeningConstant(Real k_d){
  _k_d = k_d;
}
void DampedSpring::setStiffnessConstant(Real k_s){
  _k_s=k_s;
}


Real DampedSpring::getCurrentLength()const {
	//_cA.calculateCachedValues();
	//_cB.calculateCachedValues();
	return (_cA.getWorldPosition() - _cB.getWorldPosition()).norm();
}