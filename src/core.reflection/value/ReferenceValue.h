#pragma once

#include <core.reflection/value/ITypedSerializableValue.h>

namespace nspace{
  template<typename T>
  class ReferenceValue:public virtual ITypedSerializableValue<T>{
    reflect_type(ReferenceValue);
  private:
    T & _underylingValue;
  public:
    ReferenceValue(T & value):_underylingValue(value){
      this->setValueType(typeof(T));
    }
    void notifyValueChanged(){
      this->raiseObjectChanged();
    }
  protected:

    virtual bool retrieveTypeValue(T & value)const override{value = _underylingValue; return true;}
    virtual bool storeTypedValue(const T  & value){_underylingValue = value; return true;}
  };
}
