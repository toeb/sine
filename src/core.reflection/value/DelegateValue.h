/**
* \file  E:\Projekte\dsmks\trunk\src\core\reflection\DelegateValue.h
*
* \brief Declares the delegate value class.
*/
#pragma once
#include <core.reflection/value/IModifiableValue.h>
namespace nspace{
  class DelegateModifiableValue : public IModifiableValue{
    std::function<Argument ()> _getter;
    std::function<void (Argument)> _setter;
  public:
    DelegateModifiableValue(std::function<Argument()> getter, std::function<void (Argument)> setter = std::function<void(Argument)>()):
      _getter(getter),
      _setter(setter){

    }
    
    template<typename T>
    DelegateModifiableValue& operator =(T  value){
      set(value);
      return *this;
    }
  protected:
    Argument retrieveValue()const{
      if(!(bool)_getter)return Argument();
      return _getter();
    }
    bool storeValue(Argument argument)override{
      if(!(bool)_setter)return false;
      _setter(argument);
      return true;
    }


  };
}