#include "Hexahedron.h"

using namespace IBDS;
using namespace std;

Hexahedron::Hexahedron(Real x, Real y , Real z):_xExtent(x),_yExtent(y),_zExtent(z){

}

bool Hexahedron::isInside(const Vector3D & p_wcs)const{
  Vector3D p_ocs;
  toObjectCoordinates(p_wcs,p_ocs);
  Real x = _xExtent/2;
  Real y = _yExtent/2;
  Real z = _zExtent/2;  
  if(p_wcs[0] > x)return false;
  if(p_wcs[0] < -x)return false;
  if(p_wcs[1] > y)return false;
  if(p_wcs[1] < -y)return false;
  if(p_wcs[2] > z)return false;
  if(p_wcs[2] < -z)return false;
  return true;
}

Real Hexahedron::calculateBoundingSphereRadius()const{
  //the center is in the middle of x,y,z values
  return sqrt((_xExtent*_xExtent+ _yExtent*_yExtent+_zExtent*_zExtent)/4.0); 
}