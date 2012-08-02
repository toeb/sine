#pragma once
#include <simulation/geometry/boundingVolumes/BoundingVolume.h>
#include <math/definitions.h>
#include <simulation/geometry/primitives/Sphere.h>
namespace nspace {

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