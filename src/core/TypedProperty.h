#pragma once
#include <core/Property.h>
namespace nspace{

  template<typename OwningClass, typename ValueType>
  class TypedProperty : public virtual Property{
    TYPED_OBJECT(TypedProperty);
  private:
    
    void setValue(void * object, const void * value)const{
      auto typedObject = reinterpret_cast<OwningClass*>(object);
      auto typedValue = reinterpret_cast<const ValueType*>(value);
      setTypedValue(typedObject,*typedValue);
    }
    void getValue(const void * object, void * value)const{
      auto typedObject = reinterpret_cast<const OwningClass*>(object);
      auto typedValue = reinterpret_cast<ValueType*>(value);
      *typedValue= getTypedValue(typedObject);
    }  
    
    virtual void setTypedValue(OwningClass *  object , ValueType value)const=0;
    virtual ValueType getTypedValue(const OwningClass *  object)const=0;
  };
}
