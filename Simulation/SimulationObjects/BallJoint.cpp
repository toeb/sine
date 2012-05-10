#include "BallJoint.h"
using namespace IBDS;

BallJoint::~BallJoint(void)
{
}

BallJoint::BallJoint(Connector &c1, Connector &c2, Real pTol, Real vTol):
 _cA(c1),_cB(c2),_positionTolerance(pTol), _velocityTolerance(vTol)
{}

Vector3D BallJoint::calculateDistancePreview(Real h)const{
  const Vector3D & a = _cA.previewPosition(h);
  const Vector3D & b = _cB.previewPosition(h);
  Vector3D d = b-a;
  return d;
}
void BallJoint::correctPosition(Real h) {
  // get approximation of next distance
  Vector3D d = calculateDistancePreview(h);  
  // store length of distance vector
  _positionError = d.length();
  //abort if positions are within tolerance
  if(arePositionsCorrect())return;
  //approximate velocity
  Vector3D v = (1/h) * d;
  // calculate impulse correction
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
  Vector3D  v_a =_cA.getWorldVelocity();
  Vector3D  v_b=_cB.getWorldVelocity();

  Vector3D v_rel;
  v_rel = v_b - v_a;
  
  //evaluateKInverse();
  Vector3D p_a = _KInverse * v_rel;
  Vector3D p_b = -p_a;
//  _cA.applyImpulse(p_a);
 // _cB.applyImpulse(p_b);
}

void BallJoint::evaluateKInverse() {
  const Matrix3x3 & K_a = _cA.getKMatrix();
  const Matrix3x3 & K_b = _cB.getKMatrix();

  Matrix3x3 K = K_a + K_b;
  // if the sum of the matrices is 0, do not invert it: use 0 for the inverse matrix, too, instead
  if (K.isZero())
    _KInverse = Matrix3x3::Zero();
  else 
    _KInverse = K.symmInverse();
}

void BallJoint::beforeCorrection(){
  evaluateKInverse();
}