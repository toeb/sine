#pragma once

#include <core/Object.h>

namespace nspace{
  template<typename T>
  class ITypedReadableValue : public IReadableValue{
  protected:
    bool retrieveValue(void * ptr)const{
      T * value  = reinterpret_cast<T*>(ptr);
      if(!value)return false;
      return retrieveTypeValue(*value);
    }
    virtual bool retrieveTypeValue(T & value)const=0;
  };
}