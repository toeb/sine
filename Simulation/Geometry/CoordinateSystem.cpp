#include "CoordinateSystem.h"

using namespace IBDS;
using namespace std;


CoordinateSystem::CoordinateSystem():_orientation(1,0,0,0),_p(0,0,0), _R(0),_RT(0){

}

CoordinateSystem::~CoordinateSystem(){
  if(_R)delete _R;
  if(_RT)delete _RT;
}


const Vector3D & CoordinateSystem::getPosition()const{
  return _p;    
}
void CoordinateSystem::setPosition(const Vector3D & center){
  _p.assign(center);
}

const Quaternion & CoordinateSystem::getOrientation()const{
  return _orientation;
}
void CoordinateSystem::setOrientation(const Quaternion & orientation){
  _orientation = orientation;
  _orientation.normalize();
}
  
const Matrix3x3 * CoordinateSystem::getCachedRotationMatrix()const{
  return _R;
}
const Matrix3x3 * CoordinateSystem::getCachedTransposedRotationMatrix()const{
  return _RT;
}
const Matrix3x3 & CoordinateSystem::getRotationMatrix(){
  calculateRotationMatrices();
  return *_R;
}
const Matrix3x3 & CoordinateSystem::getTransposedRotationMatrix(){
  calculateRotationMatrices();
  return *_RT;
}
  
void CoordinateSystem::toObjectCoordinates(const Vector3D & r_wcs, Vector3D & r_ocs){
  Vector3D r = r_wcs - getPosition();
  const Matrix3x3 & RT = getTransposedRotationMatrix();  
  r_ocs.assign(RT*r);
}
void CoordinateSystem::toWorldCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs){
  const Matrix3x3 & R = getRotationMatrix();
  r_wcs.assign(getPosition() + R* r_ocs);
}

void CoordinateSystem::toObjectCoordinates(const Vector3D & r_wcs, Vector3D & r_ocs)const{
  Vector3D r = r_wcs - getPosition();
  Matrix3x3 RT;
  _orientation.getMatrix3x3T(RT);
  r_ocs.assign(RT*r);
}
void CoordinateSystem::toWorldCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs)const{
  Matrix3x3 R;
  _orientation.getMatrix3x3(R);
  r_wcs.assign(getPosition() + R* r_ocs);
}

void CoordinateSystem::toObjectCoordinatesCached(const Vector3D & r_wcs, Vector3D & r_ocs)const{
  Vector3D r = r_wcs - getPosition();
  const Matrix3x3 * RT = getCachedTransposedRotationMatrix();  
  if(!RT)cout<<"RT not cached"<<endl;
  r_ocs.assign(*RT*r);
}
void CoordinateSystem::toWorldCoordinatesCached(const Vector3D & r_ocs, Vector3D & r_wcs)const{
  const Matrix3x3 * R = getCachedRotationMatrix();
  if(!R)cout<<"R not cached"<<endl;
  r_wcs.assign(getPosition() + *R* r_ocs);
}


  
  
void CoordinateSystem::calculateRotationMatrices(){
  if(!_R){
    _R = new Matrix3x3(0);
    _RT = new Matrix3x3(0);
  }
  _orientation.getMatrix3x3(*_R);
  _RT->assign(*_R);
  _RT->transposeInPlace();
}

