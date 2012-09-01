#pragma once
#include <string>
#include <urdfreader/common/NamedObject.h>
#include <urdfreader/common/ValueLookup.h>

namespace mbslib{
  
  class ModelElement:public ValueLookup, public NamedObject{
  
  };
}
