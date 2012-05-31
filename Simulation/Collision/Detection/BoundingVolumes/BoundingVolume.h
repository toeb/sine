#pragma once
#include <Simulation/Geometry/Geometry.h>
#include <Simulation/Collision/Collidable.h>

namespace IBDS{

class BoundingVolume{
private:
  bool _colliding;
  bool _updated;
  const CoordinateSystem & _coordinateSystem;
public:
  BoundingVolume(const CoordinateSystem & parentObject);
  virtual Classification classify(Geometry & geometry)const=0;
  bool isColliding()const;
  void setColliding(bool val);
  void update();
  void reset();
  bool isUpToDate()const;
  const CoordinateSystem & getParentCoordinates()const;
protected:
  virtual void updateBoundingVolume()=0;
};
class BoundingVolumeFactory{
public:
  virtual BoundingVolume * create(Geometry & geometry, const AABB & aabb)=0;
};

}