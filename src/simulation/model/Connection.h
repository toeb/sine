#pragma once

#include "ModelElement.h"
#include <urdfreader/common/Set.h>

#include <simulation/math/types.h>

namespace mbslib{
  struct Connection{
    std::string type;
    Vector3D axis;

  };

}