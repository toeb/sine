#pragma once

#include <core/Object.h>
#include <core/Observable.h>

namespace nspace{
  
class IReadableValue : public virtual Object, public virtual Observable{
  TYPED_OBJECT(IReadableValue);
  SIMPLE_PROPERTY(const Type *, ValueType){};
protected:
  virtual bool retrieveValue(void * value)const=0;
public:
  bool getByPointer(void * result)const{
    return retrieveValue(result);
  }
  IReadableValue():_ValueType(0){}
  template<typename T>
  T get()const{
    T result;
    get(result);
    return result;
  }
  template<typename T>
  bool get(T & result)const{
    return getByPointer(&result);    
  }
};



}
