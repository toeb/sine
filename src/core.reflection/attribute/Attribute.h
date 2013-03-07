#pragma once

#include <core.reflection/type/TypeInfo.h>
#include <core.reflection/type/Type.h>
#include <core.property.h>
namespace nspace{
  class Attribute{
    //DS_CLASS(Attribute);
    typedef std::string basic_property(AttributeName);
  };
  
  class AttributeTarget {
    DS_CLASS(AttributeTarget);
  public:
  };

}