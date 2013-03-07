#pragma once

#include <core.reflection/type/Type.h>
namespace nspace{

  


  template<typename T> std::shared_ptr<T> Type::createTypedInstance()const{
    return std::static_pointer_cast<T>(createInstance());
  }

  
    template<typename Container> const ConstructorInfo * Type::getConstructor(const Container & container)const{
      auto it = std::begin(container);
      auto end = std::end(container);
      std::vector<const Type*> types;
      for(;it!=end;it++){
        types.push_back(*it);
      }
      return getConstructorInfo(types);
    }

}
