#include "BallJoint.h"
using namespace nspace;

BallJoint::~BallJoint(void)
{
}

BallJoint::BallJoint(DynamicConnector &c1, DynamicConnector &c2, Real pTol, Real vTol):
 _cA(c1),_cB(c2),_positionTolerance(pTol), _velocityTolerance(vTol)
{}

void BallJoint::calculateDistancePreview(Real h, Vector3D & d)const{
  Vector3D a,b;
  _cA.previewPosition(h,a);
  _cB.previewPosition(h,b);
  d=b-a;
}
void BallJoint::correctPosition(Real h) {
  // get approximation of next distance
  Vector3D d;
  calculateDistancePreview(h,d);  
  // store length of distance vector
  _positionError = d.length();
  //abort if positions are within tolerance
  if(arePositionsCorrect())return;
  //approximate velocity
  Vector3D v = (1/h) * d;
  // calculate impulse correction
  //evaluateKInverse();
  Vector3D p_a = _KInverse * v;
  Vector3D p_b = -p_a;
  //apply correction impulse
  _cA.applyImpulse(p_a);
  _cB.applyImpulse(p_b);

}
bool BallJoint::arePositionsCorrect(){
  return _positionError < _positionTolerance;
}

void BallJoint::correctVelocity() {
  const Vector3D & v_a_wcs = _cA.getCachedWorldVelocity();
  const Vector3D & v_b_wcs = _cB.getCachedWorldVelocity();

  Vector3D v_rel;
  v_rel = v_a_wcs - v_b_wcs;
  
  Vector3D p_a = _KInverse * v_rel;
  Vector3D p_b = -p_a;
  //apply velocity correction impulse
  _cA.applyImpulse(p_a);
  _cB.applyImpulse(p_b);
}

void BallJoint::evaluateKInverse() {
  Matrix3x3  K_aa;
  Matrix3x3  K_bb;

  const Vector3D & a_wcs = _cA.getCachedWorldPosition();
  const Vector3D & b_wcs = _cB.getCachedWorldPosition();

  _cA.getKMatrix(K_aa,a_wcs,a_wcs);
  _cB.getKMatrix(K_bb,b_wcs,b_wcs);

  Matrix3x3 K = K_aa + K_bb;
  // if the sum of the matrices is 0, do not invert it: use 0 for the inverse matrix, too, instead
  if (K.isZero())
    _KInverse = Matrix3x3::Zero();
  else 
    MatrixOps::invertSymmetricMatrix(_KInverse,K);
    //Matrix3x3::symmInverse(K,_KInverse);//_KInverse = K.symmInverse();
}

void BallJoint::precompute(){
  evaluateKInverse();
}