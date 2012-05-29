#pragma once
#include <Simulation/Collision/Detection/BoundingVolumes/BoundingVolume.h>
#include <Math/Vector3D.h>
#include <Simulation/Geometry/Geometry.h>

namespace IBDS {

class BoundingSphere : public BoundingVolume{
private:
  Vector3D position;
  Real radius;
public:
  BoundingSphere(const AABB & aabb);
  Classification classify(Geometry & geometry)const;
};

class BoundingSphereFactory : public BoundingVolumeFactory{
  BoundingSphere * create(Geometry & geometry, const AABB & aabb);
};
}