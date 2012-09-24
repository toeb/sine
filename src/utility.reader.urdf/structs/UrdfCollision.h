#pragma once
#include <utility.reader.urdf/structs/UrdfOrigin.h>
#include <utility.reader.urdf/structs/UrdfGeometry.h>

#include <utility.reader.urdf/structs/UrdfElement.h>
namespace nspace{
  struct UrdfCollision : public UrdfElement{
    UrdfGeometry geometry;
  };
}