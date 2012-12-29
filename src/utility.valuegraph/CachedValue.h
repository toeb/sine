#pragma once

#include <utility.valuegraph/CachedValue.h>
#include <utility.valuegraph/TypedObservableValue.h>
#include <utility.valuegraph/ChangeTracker.h>
namespace nspace{
  template<typename T>
  class CachedValue : private ChangeTracker, public TypedObservableValue<T>{
  private:
    TypedValue<T> & _value;
  public:
    CachedValue(TypedValue<T> & value):_value(value),ChangeTracker(value){cache();}

    void cache(){
      //sets cache to to current value of underlying var
      this->set(_value.get());
      access();
    }

    TypedValue<T> & source(){
      return _value;
    }

    inline bool dirty()const{
      return hasChanged();
    }
  };
}
