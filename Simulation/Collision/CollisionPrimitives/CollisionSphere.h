#pragma once

#include <Simulation/Geometry/Primitives/Sphere.h>
#include <Simulation/Collision/Collidable.h>
#include <Simulation/Core/IUpdateable.h>

namespace IBDS{
class CollisionSphere : public virtual Collidable, public virtual Sphere, public virtual IUpdatable{
private:
  GeometricObject & _object;
public:
  CollisionSphere(GeometricObject & obj):_object(obj){

  }
  void update(Real t, Real h);
};
}