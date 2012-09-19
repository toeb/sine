#pragma once

#include <simulation.access/IValue.h>
namespace nspace{

template<typename T>
class TypedValue : public IValue{
  T & _value;
public:
  T & value(){
    return _value;
  }
  const T & value()const{
    return _value;
  }
  TypedValue(T & val):_value(val){
    
  }
  virtual void toString(std::ostream & out)const{
    out << get();
  };
 
  void set(const T & type){
    _value = type;
  }
  T & get(){
    return _value;
  }
  const T & get()const {
    return _value;
  }
protected:
  void set(const void * value){
    const T * typedValue = static_cast<const T*>(value);
    _value = *typedValue;
  }
  void get(void * value){
    T * typedValue = static_cast<T*>(value);
    *typedValue = _value;
  }
};

}
