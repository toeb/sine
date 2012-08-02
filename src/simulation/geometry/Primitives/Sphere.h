#pragma once
#include <simulation/geometry/Geometry.h>
namespace nspace{
class Sphere : public Geometry{
private:
  Real _radius;
public:
  static const TypeId type;
  const TypeId getType()const;
  Sphere(Real radius=1.0);

  Real calculateBoundingSphereRadius()const;

  inline Real radius()const{return _radius;};
  void setRadius(Real radius);

  
  void projectOCS(const Axis & axis_ocs, Interval & result)const;
  
  Classification classify(const BoundingVolume & volume)const;
  
protected:
  virtual void onRadiusChanged(){}
};
}

