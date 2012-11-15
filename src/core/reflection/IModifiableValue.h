#pragma once

#include <core/reflection/IReadableValue.h>

namespace nspace{
  
class IModifiableValue : public IReadableValue{
  TYPED_OBJECT(IModifiableValue);
private:
  bool changeValue(const void * value){
    bool cancel = false;
    valueChanging(value,cancel);
    if(cancel)return false;    
    bool success = storeValue(value);
    if(success) valueChanged(value);
    return success;
  }
protected:
  virtual bool storeValue(const void * value)=0;
  virtual void valueChanging(const void * newvalue, bool & cancel){}
  virtual void valueChanged(const void * newvalue){}
public:
  bool setByPointer(const void * value){return changeValue(value);};
  template<typename T>
  bool set(const T & value){
    return setByPointer(&value);
  }
};

}