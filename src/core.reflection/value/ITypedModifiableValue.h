#pragma once


#include <core.reflection/value/IModifiableValue.h>
namespace nspace{
  template<typename T>
  class ITypedModifiableValue :  public virtual IModifiableValue{
  public:
    ITypedModifiableValue(){
      setValueType(typeof(T));
    }
  protected:
    virtual bool storeTypedValue(const T  & value)=0;
    virtual bool retrieveTypeValue(T & value)const=0;

    bool storeValue(const void * ptr){
      const T* value = reinterpret_cast<const T*>(ptr);
      if(!value)return false;
      return storeTypedValue(*value);
    }
    bool retrieveValue(void * ptr)const{
      T * value  = reinterpret_cast<T*>(ptr);
      if(!value)return false;
      return retrieveTypeValue(*value);
    }
  };
}
