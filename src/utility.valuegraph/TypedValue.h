#pragma once


#include <config.h>
#include <utility.valuegraph/Value.h>

namespace nspace{
  
template< typename T>
class TypedValue : public virtual Value{
private:
  T _value;
public:
  TypedValue(const T & init):_value(init){

  }
  TypedValue(){}
  virtual const void * pointer()const{
    return &_value;
  }
  virtual void * pointer(){
    return &_value;
  }

  operator T() const {
    return get();
  }
  TypedValue<T> & operator=(const T & val){
    set(val);
    return *this;
  }

  T operator()()const{
    return get();
  }

  T get()const{return _value;}
  T & reference(){return _value;}
  const T & reference()const{return _value;}
  void set(const T & val){
    if(_value==val)return;
    _value = val;
    notifyChange();
  }
protected:
};

}