#pragma once
#include <Simulation/Geometry/BoundingVolumes/BoundingVolume.h>
#include <Math/Vector3D.h>
#include <Simulation/Geometry/Primitives/Sphere.h>
namespace IBDS {

class BoundingSphere : public BoundingVolume, public virtual Sphere {
private:
  //position in parent coordinates ie the position this sphere has in the parent coordinate system
  Vector3D _p_pcs;
public:
  BoundingSphere(const Vector3D & min, const Vector3D & max, const CoordinateSystem & coordinateSystem);
  void projectPCS(const Axis & axis, Interval & result)const;
  void updateBoundingVolume();
  const Vector3D & getPositionPCS()const;
};

class BoundingSphereFactory : public BoundingVolumeFactory{
  BoundingSphere * create(const Vector3D & min, const Vector3D & max,const CoordinateSystem & parentObject);
};
}