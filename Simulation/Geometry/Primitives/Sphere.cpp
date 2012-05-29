#include "Sphere.h"

using namespace std;
using namespace IBDS;

Classification Sphere::classify(const AABB & aabb_ocs)const{
  Vector3D center;
  aabb_ocs.getCenter(center);
  Axis axis;
  if(center.length2()==0)center.assign(Vector3D::e1());
  axis.n = center;
  axis.n.normalize();
  // axis of separation is the center of aabb to center of sphere

  Interval aabbInterval;
  Interval sphereInterval(-_radius,_radius);

  aabb_ocs.projectOCS(axis,aabbInterval);
  
  if(aabbInterval.disjoint(sphereInterval))return Classification::OUTSIDE;
  if(aabbInterval.subsetOf(sphereInterval)){
    return Classification::INSIDE;
  }
  return Classification::BOTH;

}

Classification Sphere::classify(const Vector3D & p, Real radius)const{
  
  Axis axis;
  if(p.length2()==0){
    axis.n.assign(Vector3D::e1());
  }else{
    axis.n = p;
    axis.n.normalize();
  }
  // axis of separation is the center of aabb to center of sphere

  Interval intervalA;
  Interval intervalB(-_radius,_radius);

  Real val = axis.projectOnAxis(p);
  intervalA.a=val-radius;
  intervalA.b=val+radius;

  if(intervalA.disjoint(intervalB))return Classification::OUTSIDE;
  if(intervalA.subsetOf(intervalB)){
    return Classification::INSIDE;
  }
  return Classification::BOTH;
}
bool Sphere::boundaryIntersects(const AABB & aabb_ocs)const{
  return false;
}

Sphere::Sphere(Real radius){
  _radius = radius;
}
bool Sphere::isInsideOCS(const Vector3D & p_ocs)const{
  Real lengthSquared = p_ocs.length2();
  if(_radius*_radius < lengthSquared)return false;
  return true;
}

Real Sphere::calculateBoundingSphereRadius()const{
  return _radius;
}


Real Sphere::getRadius()const{
  return _radius;
}
void Sphere::setRadius(Real radius){
  if(radius < 0){
    cout<<"Sphere radius was smaller than zero";
    return;
  }
  _radius = radius;
  onRadiusChanged();
}

void Sphere::fitInto(const AABB & aabb){
    Vector3D position;
    aabb.getCenter(position);
    setPosition(position);
    //setRadius((aabb.min - position).length());
}


  
  void Sphere::projectOCS(const Axis & axis_ocs, Interval & result)const{
    Real val = axis_ocs.projectOnAxis(-axis_ocs.p);

    result.a = val - _radius;
    result.b = val +  _radius;
  }
