#pragma once
#include <utility.reader.urdf/structs/UrdfElement.h>
#include <math/definitions.h>

namespace nspace{

struct UrdfLink : public UrdfElement{
  Matrix3x3 inertia;
  Real mass;

};
}