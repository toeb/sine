#pragma once
#include <urdfreader/parsers/urdf/structs/UrdfElement.h>
#include <simulation/math/types.h>

namespace mbslib{

struct UrdfLink : public UrdfElement{
  Matrix3x3 inertia;
  Real mass;

};
}