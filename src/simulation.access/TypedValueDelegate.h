#pragma once

#include <simulation.access/IValue.h>
namespace nspace{

template<typename T>
class TypedValueDelegate : public IValue{
private:
  std::function<void (const T & )> _setter;
  std::function<T ()> _getter;
public:  
  TypedValueDelegate(
    std::function<T  ()> getter,
    std::function<void (const T & )> setter)
    :_getter(getter),_setter(setter){

  }
  virtual void toString(std::ostream & out)const{
    out << get();
  };
  virtual void fromString(std::istream & instream){
    T value;
    instream >> value;
    set(value);
  }

  void set(const T & v){
    _setter(v);
  }
  T  get(){
    return _getter();
  }
   T  get()const{
    return _getter();
  }


  void set(const void * value){
    const T * typedValue = static_cast<const T*>(value);
    if(!_setter)return;
    _setter(*typedValue);
  }
  void get(void * value){
    T * typedValue = static_cast<T*>(value);
    *typedValue = _getter();
  }
};

}
