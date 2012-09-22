#pragma once

#include <utility.reader.urdf/structs/UrdfElement.h>
#include <math/core.h>
#include <string>

namespace nspace{

struct UrdfJoint : public UrdfElement{
  Vector3D axis;
  std::string type;
};
}