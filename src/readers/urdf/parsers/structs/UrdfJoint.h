#pragma once

#include <urdfreader/parsers/urdf/structs/UrdfElement.h>
#include <simulation/math/types.h>
#include <string>

namespace mbslib{

struct UrdfJoint : public UrdfElement{
  Vector3D axis;
  std::string type;
};
}