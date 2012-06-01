#pragma once

#include <Simulation/Geometry/CoordinateSystem.h>
#include <Simulation/Geometry/AABB.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingVolume.h>
namespace IBDS{

class Geometry : public virtual CoordinateSystem{
public:  
  virtual void projectOCS(const Axis & axis_ocs, Interval & result)const{}; 
  virtual void project(const Axis & axis_wcs, Interval & result)const;
  
  virtual void getBoundingBoxOCS(AABB & aabb_ocs)const;
  virtual void getBoundingBox(AABB & aabb_wcs)const;

  virtual Real calculateBoundingSphereRadius()const;

  virtual Classification classify(const BoundingVolume & volume)const{return Classification::UNCLASSIFIED;}

};

}