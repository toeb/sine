#pragma once

#include <core.property.h>
#include <string>

namespace nspace{
  class Attribute{
    typedef std::string basic_property(AttributeName);
  public:
    virtual ~Attribute();
  };
}