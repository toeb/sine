#pragma once

#include <core.reflection.h>
#include <map>
namespace nspace{
  namespace core{
    namespace serialization{
      class DeserializationContext{
        std::map<int,std::shared_ptr<void>> _pointerMap;
      };
    }
  }
}