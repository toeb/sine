#pragma once

#include <math/core.h>
#include <simulation.kinematics/CoordinateSystem.h>

namespace nspace{
  
struct Origin{
  operator CoordinateSystem(){
    CoordinateSystem result;
    result.position()=xyz;
    result.orientation().fromRollPitchYaw(rpy);
    return result;
  }
  Origin():xyz(0,0,0),rpy(0,0,0){

  }
  Vector3D xyz;
  Vector3D rpy;
};


}