#pragma once
#include <Simulation/Geometry/Geometry.h>
namespace IBDS{

class BoundingVolume{
public:
  virtual Classification classify(Geometry & geometry)const=0;
};
class BoundingVolumeFactory{
public:
  virtual BoundingVolume * create(Geometry & geometry, const AABB & aabb)=0;
};

}