#pragma once
#include <Simulation/Collision/Detection/BoundingVolumes/BoundingVolume.h>
#include <Math/Vector3D.h>
#include <Simulation/Geometry/Geometry.h>
#include <Simulation/Geometry/Primitives/Sphere.h>
namespace IBDS {

class BoundingSphere : public BoundingVolume, public virtual Sphere {
private:
  Vector3D _p_ocs;
public:
  BoundingSphere(const AABB & aabb, const CoordinateSystem & coordinateSystem);
  Classification classify(Geometry & geometry)const;
  void updateBoundingVolume();
  const Vector3D & getPositionOCS()const;
};

class BoundingSphereFactory : public BoundingVolumeFactory{
  BoundingSphere * create(Geometry & geometry, const AABB & aabb);
};
}