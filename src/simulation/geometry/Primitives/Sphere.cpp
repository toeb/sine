#include "Sphere.h"
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>
using namespace std;
using namespace nspace;

const TypeId Sphere::type = "Sphere";

const TypeId Sphere::getType()const{
  return type;
}

Classification classifyBoundingBox(const BoundingBox & aabb_ocs, const Sphere & sphere){
  Real radius = sphere.radius();

  Vector3D center;
  aabb_ocs.getCenter(center);
  Axis axis;
  if(center.length2()==0)center.assign(Vector3D::UnitX());
  axis.n = center;
  axis.n.normalize();
  // axis of separation is the center of aabb to center of sphere

  Interval aabbInterval;
  Interval sphereInterval(-radius,radius);

  aabb_ocs.projectOCS(axis,aabbInterval);
  
  if(aabbInterval.disjoint(sphereInterval))return Classification::OUTSIDE;

  if(aabbInterval.isSubsetOf(sphereInterval)){
    return Classification::INSIDE;
  }
  return Classification::BOTH;

}

Classification classifySphere(const BoundingSphere & boundingSphere, const Sphere & sphere){
  Axis direction;
  // the axis on which to project is boundingSphere.p_ocs-sphere.p_ocs/|| boundingSphere.p_ocs-sphere.p_ocs||
  direction.n = boundingSphere.getPositionPCS();   
  direction.n.normalize();

  Interval boundingSphereInterval, sphereInterval;
  
  //project both spheres on the axis
  sphere.projectOCS(direction,sphereInterval);

  //bounding sphere needs custom projection
  
  boundingSphere.projectPCS(direction,boundingSphereInterval);
    

  // if the spheres do not overlap at all the bounding sphere is outside
  if(boundingSphereInterval.disjoint(sphereInterval))return Classification::OUTSIDE;

  // if the spheres overlap and the boundinsphere is inside the sphere return INSIDE
  if(boundingSphereInterval.isSubsetOf(sphereInterval)){
    return Classification::INSIDE;
  }
  //else both applies
  return Classification::BOTH;
}

Classification Sphere::classify(const BoundingVolume & volume)const{
  const BoundingSphere * bSphere = dynamic_cast<const BoundingSphere*>(&volume);
  if(bSphere){
    return classifySphere(*bSphere,*this);
  }

  const BoundingBox * aabb = dynamic_cast<const BoundingBox*>(&volume);
  if(aabb){
    return classifyBoundingBox(*aabb,*this);
  }

  return UNCLASSIFIED;
}

Sphere::Sphere(Real radius){
  _radius = radius;
}


Real Sphere::calculateBoundingSphereRadius()const{
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


  
void Sphere::projectOCS(const Axis & axis_ocs, Interval & result)const{
  Real val = axis_ocs.projectOnAxis(Vector3D::Zero());

  result.a = val - _radius;
  result.b = val +  _radius;
}
