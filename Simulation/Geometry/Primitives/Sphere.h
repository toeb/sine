#pragma once
#include <Simulation/Geometry/Geometry.h>
namespace IBDS{
class Sphere : public virtual Geometry{
private:
  Real _radius;
public:
  Sphere(Real radius=1.0);
  bool isInsideOCS(const Vector3D & p_ocs)const;
  Real calculateBoundingSphereRadius()const;
  Real getRadius()const;
  void setRadius(Real radius);

  bool boundaryIntersects(const AABB & aabb)const;

  void fitInto(const AABB & aabb);
  
  void projectOCS(const Axis & axis_ocs, Interval & result)const;
  Classification classify(const AABB & aabb)const;
  Classification classify(const Vector3D & p, Real radius)const;
protected:
  virtual void onRadiusChanged(){}
};
}

