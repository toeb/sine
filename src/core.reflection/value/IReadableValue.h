#pragma once

#include <core/Object.h>
#include <core/Observable.h>
#include <core.properties.h>
#include <core.reflection/type/TypeInfo.h>

namespace nspace{
  class IReadableValue : public virtual Object, public virtual Observable{
    DS_CLASS_DECLARATION(IReadableValue);
    
    ConstTypePtr basic_property(ValueType);
  protected:
    virtual bool retrieveValue(void * value)const=0;
  public:
    bool getByPointer(void * result)const;
    IReadableValue();
    template<typename T> T get()const;
    template<typename T> bool get(T & result)const;
  };



  template<typename T> T IReadableValue::get()const{
    T result;
    get(result);
    return result;
  }
  template<typename T> bool IReadableValue::get(T & result)const{
    return getByPointer(&result);
  }
}
