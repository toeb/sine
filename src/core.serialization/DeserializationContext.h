#pragma once

#include <core.reflection.h>
#include <map>
namespace nspace{
  namespace core{
    namespace serialization{
      class DeserializationContext{
        std::map<int,Argument> _pointerMap;
      public:
        Argument getPointer(int id){
          auto it = _pointerMap.find(id);
          if(it==std::end(_pointerMap))return Argument();
          return it->second;
        }
        Argument requirePointer(int id,Argument arg){
          auto pointer = getPointer(id);
          if(pointer.isValid())return pointer;
          _pointerMap[id]=arg;
          return getPointer(id);
        }
      };
    }
  }
}