#pragma once
#include <core.reflection/member/property/PropertyInfo.h>
#include <core.serialization/Serialization.h>
namespace nspace{
  template<typename OwningClass, typename ValueType>
  class TypedProperty : public virtual PropertyInfo{
    TYPED_OBJECT(TypedProperty);
  public:
    TypedProperty();
  private:
    const void * getConstPointer(const Object * object)const;
    void * getMutablePointer(Object * object)const;
    virtual const ValueType * getConstTypedPointer(const OwningClass*)const;
    virtual ValueType * getMutableTypedPointer(OwningClass* )const;
    void setValue(Object * object, const void * value)const;
    void unsafeSetValue(void * object, const void * value)const;
    void getValue(const  Object * ptr, void * value)const;
    void unsafeGetValue(const  void * ptr, void * value)const;
    virtual bool deserialize(Object * ptr, std::istream & in)const;
    virtual bool serialize(Object * object, std::ostream & out)const;
    virtual void setTypedValue(OwningClass *  object , ValueType value)const=0;
    virtual ValueType getTypedValue(const OwningClass *  object)const=0;
  };

  // Implementation
  template<typename OwningClass, typename ValueType>
  const ValueType * TypedProperty<OwningClass,ValueType>::getConstTypedPointer(const OwningClass*)const{return 0;}
  template<typename OwningClass, typename ValueType>  
  ValueType * TypedProperty<OwningClass,ValueType>::getMutableTypedPointer(OwningClass* )const{return 0;}
  template<typename OwningClass, typename ValueType>
  TypedProperty<OwningClass,ValueType>::TypedProperty(){
    setOwningType(typeof(OwningClass));
    //setPropertyType(&TypeDataProvider<ValueType>::getTypeData());
  }
  template<typename OwningClass, typename ValueType>
  const void * TypedProperty<OwningClass,ValueType>::getConstPointer(const Object * object)const{
    auto typedObject = dynamic_cast<const OwningClass*>(object);
    return reinterpret_cast<const void*>(getConstTypedPointer(typedObject));
  }
  template<typename OwningClass, typename ValueType>
  void * TypedProperty<OwningClass,ValueType>::getMutablePointer(Object * object)const{
    auto typedObject = dynamic_cast< OwningClass*>(object);
    return reinterpret_cast<void*>(getMutableTypedPointer(typedObject));
  }

  template<typename OwningClass, typename ValueType>
  void TypedProperty<OwningClass,ValueType>::setValue(Object * object, const void * value)const{
    auto typedObject = dynamic_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<const ValueType*>(value);
    setTypedValue(typedObject,*typedValue);
  }
  template<typename OwningClass, typename ValueType>
  void TypedProperty<OwningClass,ValueType>::getValue(const Object * object, void * value)const{
    auto typedObject = dynamic_cast<const OwningClass*>(object);
    if(!typedObject)return;
    auto typedValue = reinterpret_cast<ValueType*>(value);
    *typedValue= getTypedValue(typedObject);
  }
    template<typename OwningClass, typename ValueType>
  void TypedProperty<OwningClass,ValueType>::unsafeSetValue(void * object, const void * value)const{
    auto typedObject = static_cast<OwningClass*>(object);
    auto typedValue = static_cast<const ValueType*>(value);
    setTypedValue(typedObject,*typedValue);
  }
  template<typename OwningClass, typename ValueType>
  void TypedProperty<OwningClass,ValueType>::unsafeGetValue(const void * object, void * value)const{
    auto typedObject = static_cast<const OwningClass*>(object);
    auto typedValue = static_cast<ValueType*>(value);
    *typedValue= getTypedValue(typedObject);
  }
  template<typename OwningClass, typename ValueType>
  bool TypedProperty<OwningClass,ValueType>::deserialize(Object * object, std::istream & in)const{
    OwningClass * owningClass = dynamic_cast<OwningClass*>(object);
    if(!owningClass)return false;
    ValueType value;
    getValue(owningClass,&value);
    if(getCustomDeserializer()){
      if(!(getCustomDeserializer()->deserialize(&value,in)))return false;
    }else{
      if(!Deserializer<ValueType>::deserialize(&value,in))return false;
    }

    setTypedValue(owningClass,value);
    return true;
  }
  template<typename OwningClass, typename ValueType>
  bool TypedProperty<OwningClass,ValueType>::serialize(Object * object, std::ostream & out)const{
    OwningClass * owningClass = dynamic_cast<OwningClass*>(object);
    ValueType value = getTypedValue(owningClass);
    if(getCustomSerializer()){
      if(!(getCustomSerializer()->serialize(out,&value)))return false;
    }else{
      if(!Serializer<ValueType>::serialize(out,&value))return false;
    }
    return true;
  }
}
