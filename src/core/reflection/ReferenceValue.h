#pragma once

#include <core/reflection/ITypedSerializableValue.h>

namespace nspace{
  

template<typename T>
class ReferenceValue:public virtual ITypedSerializableValue<T>{
  TYPED_OBJECT(ReferenceValue);
private:
  T & _underylingValue;
public:
  ReferenceValue(T & value):_underylingValue(value){setValueType(typeof(T));}
  void notifyValueChanged(){
    this->raiseObjectChanged();
  }
protected:  
  
  virtual bool retrieveTypeValue(T & value)const{value = _underylingValue; return true;}
  virtual bool storeTypedValue(const T  & value){_underylingValue = value; return true;}
};
}
