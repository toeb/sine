#pragma once

#include <string>
#include <visualization/Color.h>

#include <config.h>
namespace nspace{
  struct UrdfMaterial{
    std::string name;
    Color color;
    std::string texturefile;
  };

}