#pragma once

#include <Simulation/Kinematics/CoordinateSystem.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingBox.h>
namespace IBDS{

class Geometry : public ISimulationObject{
private:
  CoordinateSystem _coordinateSystem;
public:  
  inline CoordinateSystem & coordinates(){return _coordinateSystem;}
  inline const CoordinateSystem & coordinates()const{return _coordinateSystem;}
  
  virtual void projectOCS(const Axis & axis_ocs, Interval & result)const{}; 
  virtual void project(const Axis & axis_wcs, Interval & result)const;
  
  virtual void getBoundingBoxOCS(BoundingBox & aabb_ocs)const;
  virtual void getBoundingBox(BoundingBox & aabb_wcs)const;

  virtual Real calculateBoundingSphereRadius()const;
  
  virtual Classification classify(const BoundingVolume & volume)const{return Classification::UNCLASSIFIED;}

};

}