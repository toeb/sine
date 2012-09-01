#pragma once

#include <simulation/math/types.h>

namespace mbslib{
  
struct Origin{
  operator CoordinateSystem(){
    CoordinateSystem result;
    result.position()=xyz;
    result.orientation().setFromRollPitchYaw(rpy);
    return result;
  }
  Origin():xyz(0,0,0),rpy(0,0,0){

  }
  Vector3D xyz;
  Vector3D rpy;
};


}