#pragma once

#include <readers/urdf/structs/UrdfElement.h>
#include <math/definitions.h>
#include <string>

namespace nspace{

struct UrdfJoint : public UrdfElement{
  Vector3D axis;
  std::string type;
};
}