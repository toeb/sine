#pragma once

#include <core/reflection/ITypedSerializableValue.h>

namespace nspace{
  

template<typename T>
class DelegateValue : public virtual ITypedSerializableValue<T>{
  TYPED_OBJECT(DelegateValue);
public:
  typedef std::function<T () > Getter;
  typedef std::function<void (T)> Setter; 

  DelegateValue(Getter getter, Setter setter):_getter(getter), _setter(setter){}
  
  virtual bool retrieveTypeValue(T & value)const{if(!_getter)return false; value = _getter(); return true;}
  virtual bool storeTypedValue(const T  & value){if(!_setter)return false; _setter(value); return true;}
private:
  Getter _getter;
  Setter _setter;
};

}