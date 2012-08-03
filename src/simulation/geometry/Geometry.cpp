#include "Geometry.h"

using namespace nspace;



void Geometry::getBoundingBoxOCS(BoundingBox & aabb)const{
  Axis x,y,z;
  x.n = Matrix3x3::Identity().v[0];
  y.n = Matrix3x3::Identity().v[1];
  z.n = Matrix3x3::Identity().v[2];
  Interval ix,iy,iz;

  projectOCS(x,ix);
  projectOCS(y,iy);
  projectOCS(z,iz);
  
  aabb.minValue()(0)= ix.a;
  aabb.minValue()(1)= iy.a;
  aabb.minValue()(2)= iz.a;
  
  aabb.maxValue()(0)= ix.b;
  aabb.maxValue()(1)= iy.b;
  aabb.maxValue()(2)= iz.b;


  Real min =DBL_MAX;
  Real max=-DBL_MAX;
  for(int i = 0; i < 3; i++){
    if(min > aabb.minValue()(i))min = aabb.minValue()(i);
    if(max < aabb.maxValue()(i))max = aabb.maxValue()(i);
  }
  aabb.minValue().set(min,min,min);
  aabb.maxValue().set(max,max,max);
}


void Geometry::getBoundingBox(BoundingBox & aabb)const{
  Axis x,y,z;
  x.n = Matrix3x3::Identity().v[0];
  y.n = Matrix3x3::Identity().v[1];
  z.n = Matrix3x3::Identity().v[2];
  Interval ix,iy,iz;

  project(x,ix);
  project(y,iy);
  project(z,iz);
  
  aabb.minValue()(0)= ix.a;
  aabb.minValue()(1)= iy.a;
  aabb.minValue()(2)= iz.a;
  
  aabb.maxValue()(0)= ix.b;
  aabb.maxValue()(1)= iy.b;
  aabb.maxValue()(2)= iz.b;
}

void Geometry::project(const Axis & axis_wcs, Interval & interval)const{
  Axis axis_ocs;
  coordinates().toObjectCoordinates(axis_wcs.p,axis_ocs.p);
  coordinates().toObjectCoordinates(axis_wcs.n+coordinates().position(),axis_ocs.n);
  axis_ocs.n.normalize();
  projectOCS(axis_ocs,interval);

}

Real Geometry::calculateBoundingSphereRadius()const{
  BoundingBox bb;
  getBoundingBoxOCS(bb);
  Vector3D delta = bb.maxValue()-bb.minValue();
  return delta.length()/2;
}