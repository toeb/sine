#pragma once
#include <Simulation/Geometry/Geometry.h>
namespace IBDS{
class Sphere : public Geometry{
private:
  Real _radius;
public:
  static const TypeId type;
  const TypeId getType()const;
  Sphere(Real radius=1.0);

  Real calculateBoundingSphereRadius()const;

  Real getRadius()const;
  void setRadius(Real radius);

  
  void projectOCS(const Axis & axis_ocs, Interval & result)const;
  
  Classification classify(const BoundingVolume & volume)const;
  
protected:
  virtual void onRadiusChanged(){}
};
}

