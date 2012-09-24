#pragma once

#include <utility.reader.urdf/structs/UrdfElement.h>
#include <math/core.h>
#include <string>

namespace nspace{
  struct UrdfJointLimits{
    UrdfJointLimits():lowerPositionLimit(-REAL_MAX),upperPositionLimit(REAL_MAX),effortLimit(REAL_MAX),velocityLimit(REAL_MAX){}
    Real lowerPositionLimit;
    Real upperPositionLimit;
    Real effortLimit;
    Real velocityLimit;
  };
struct UrdfJoint : public UrdfElement{
  UrdfJoint():limits(0){}
  Vector3D axis;
  std::string type;
  UrdfJointLimits * limits;
};
}