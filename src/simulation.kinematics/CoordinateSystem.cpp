#include "CoordinateSystem.h"

using namespace nspace;
using namespace std;


CoordinateSystem::CoordinateSystem(): _R(0),_RT(0),position(&Vector3D::Zero()),orientation(&Quaternion::ZeroRotation()){
  orientation() = Quaternion::ZeroRotation();
}

CoordinateSystem::CoordinateSystem(const Vector3D & p, const Quaternion & q):
position(&p),orientation(&q),
 _R(0),_RT(0){

  calculateRotationMatrices();
}


CoordinateSystem::~CoordinateSystem(){
  if(_R)delete _R;
  if(_RT)delete _RT;
}

const CoordinateSystem & CoordinateSystem::identity(){
  static CoordinateSystem system(Vector3D::Zero(),Quaternion::ZeroRotation());
  return system;
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
  Vector3D r = r_wcs - position();
  const Matrix3x3 & RT = getTransposedRotationMatrix();  
  r_ocs=RT*r;
}
void CoordinateSystem::fromObjectCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs){
  const Matrix3x3 & R = getRotationMatrix();
  r_wcs =position() + R* r_ocs;
}

void CoordinateSystem::toObjectCoordinates(const Vector3D & r_wcs, Vector3D & r_ocs)const{
  Vector3D r = r_wcs - position();
  Matrix3x3 RT;
  orientation().toTransposedRotationMatrix(RT);
  r_ocs =RT*r;
}
void CoordinateSystem::fromObjectCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs)const{
  Matrix3x3 R;
  orientation().toRotationMatrix(R);
  r_wcs = position() + R* r_ocs;
}

void CoordinateSystem::toObjectCoordinatesCached(const Vector3D & r_wcs, Vector3D & r_ocs)const{
  Vector3D r = r_wcs - position();
  const Matrix3x3 * RT = getCachedTransposedRotationMatrix();  
  if(!RT)cout<<"RT not cached"<<endl;
  r_ocs = *RT*r;
}
void CoordinateSystem::fromObjectCoordinatesCached(const Vector3D & r_ocs, Vector3D & r_wcs)const{
  const Matrix3x3 * R = getCachedRotationMatrix();
  if(!R)cout<<"R not cached"<<endl;
  r_wcs= position() + *R* r_ocs;
}



  namespace nspace{
std::ostream & operator << (std::ostream & o, const CoordinateSystem & coordinates){
  o << "position: (" <<coordinates.position().x()  <<", "<<coordinates.position().y()  <<", "<<coordinates.position().z()<< ") orientation: "<<coordinates.orientation();
  return o;
}
  }


void CoordinateSystem::fromObjectCoordinates(const CoordinateSystem & coords_ocs,CoordinateSystem & result)const{
  fromObjectCoordinates(coords_ocs.position(),result.position());
  result.orientation() = coords_ocs.orientation()*orientation();  
}
void CoordinateSystem::toObjectCoordinates(const CoordinateSystem & coords_wcs,CoordinateSystem & result)const{
  toObjectCoordinates(coords_wcs.position(),result.position());
  ERROR("method not implemented completely");
}
  
  
void CoordinateSystem::calculateRotationMatrices(){
  if(!_R){
    _R = new Matrix3x3;
    _RT = new Matrix3x3;
  }
  orientation().toRotationMatrix(*_R);
  *_RT=*_R;
  _RT->transpose();
}

