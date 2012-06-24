#include "Geometry.h"

using namespace IBDS;



void Geometry::getBoundingBoxOCS(AABB & aabb)const{
  Axis x,y,z;
  x.n = Matrix3x3::Identity().v[0];
  y.n = Matrix3x3::Identity().v[1];
  z.n = Matrix3x3::Identity().v[2];
  Interval ix,iy,iz;

  projectOCS(x,ix);
  projectOCS(y,iy);
  projectOCS(z,iz);
  
  aabb.min[0]= ix.a;
  aabb.min[1]= iy.a;
  aabb.min[2]= iz.a;
  
  aabb.max[0]= ix.b;
  aabb.max[1]= iy.b;
  aabb.max[2]= iz.b;

  Real min =DBL_MAX;
  Real max=-DBL_MAX;
  for(int i = 0; i < 3; i++){
    if(min > aabb.min[i])min = aabb.min[i];
    if(max < aabb.max[i])max = aabb.max[i];
  }
  aabb.min.set(min,min,min);
  aabb.max.set(max,max,max);
}


void Geometry::getBoundingBox(AABB & aabb)const{
  Axis x,y,z;
  x.n = Matrix3x3::Identity().v[0];
  y.n = Matrix3x3::Identity().v[1];
  z.n = Matrix3x3::Identity().v[2];
  Interval ix,iy,iz;

  project(x,ix);
  project(y,iy);
  project(z,iz);
  
  aabb.min[0]= ix.a;
  aabb.min[1]= iy.a;
  aabb.min[2]= iz.a;
  
  aabb.max[0]= ix.b;
  aabb.max[1]= iy.b;
  aabb.max[2]= iz.b;
}

void Geometry::project(const Axis & axis_wcs, Interval & interval)const{
  Axis axis_ocs;
  toObjectCoordinates(axis_wcs.p,axis_ocs.p);
  toObjectCoordinates(axis_wcs.n+getPosition(),axis_ocs.n);
  axis_ocs.n.normalize();
  projectOCS(axis_ocs,interval);

}

Real Geometry::calculateBoundingSphereRadius()const{
  AABB aabb;
  getBoundingBoxOCS(aabb);
  Vector3D delta = aabb.max-aabb.min;
  return delta.length()/2;
}