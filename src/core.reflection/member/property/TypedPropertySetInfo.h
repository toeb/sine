#pragma once

#include <core/reflection/PropertySetInfo.h>
#include <core/reflection/TypedProperty.h>

namespace nspace{
  template<typename OwningClass, typename ValueType>
  class TypedPropertySetInfo:public virtual TypedProperty<OwningClass, Set<ValueType> >, public virtual PropertySetInfo{
    TYPED_OBJECT(TypedPropertySetInfo);
  public:
    virtual Set<ValueType> & getMutableSetReference( OwningClass * object )const=0;
    virtual const Set<ValueType> & getConstSetReference(const OwningClass * object )const=0;
    virtual uint getElementCount(Object * ptr)const;

    TypedPropertySetInfo();
    // TypedProperty Implementation
    void setTypedValue(OwningClass * object, Set<ValueType>  value)const;
    Set<ValueType> getTypedValue(const OwningClass * object)const;

    bool addObserver(Object * ptr,ObjectObserver* observer)const;
    bool removeObserver(Object * ptr,ObjectObserver* observer)const;
    const Set<ValueType> * getConstTypedPointer(const OwningClass * object)const;
    Set<ValueType> * getMutableTypedPointer(OwningClass * object)const;

    bool addTypedElement(OwningClass & object, ValueType & value)const;
    bool removeTypedElement(OwningClass & object, const ValueType & value)const;

    bool addElement(Object * object, void*value)const;
    bool removeElement(Object * object, const void*value)const;
    bool setTypedElement(OwningClass * object, uint i, const ValueType * value )const;
    bool getTypedElement(const OwningClass * object, uint i, ValueType * value )const;
    // sets the value of the property set at i
    bool setElement(Object * object, uint i, const void * value)const;
    // gets the value of the property set at i
    bool getElement(const Object * object, uint i, void * value)const;
    bool deserializeElement(Object * ptr, uint i, std::istream & in)const;
    bool serializeElement(Object * ptr,uint i,  std::ostream & out)const;
  };

  // Implementation

  template<typename OwningClass, typename ValueType>
  TypedPropertySetInfo<OwningClass,ValueType>::TypedPropertySetInfo(){
    setElementType(typeof(ValueType));
    setPropertyType(typeof(Set<ValueType>));
    setOwningType(typeof(OwningClass));
  }

  template<typename OwningClass, typename ValueType>
  void  TypedPropertySetInfo<OwningClass,ValueType>::setTypedValue(OwningClass * object, Set<ValueType>  value)const{
    getMutableSetReference(object)=value;
  }
  template<typename OwningClass, typename ValueType>
  Set<ValueType>  TypedPropertySetInfo<OwningClass,ValueType>::getTypedValue(const OwningClass * object)const{
    return getConstSetReference(object);
  }

  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::addObserver(Object * object,ObjectObserver* observer)const{
    auto typedObject = dynamic_cast<OwningClass*>(object);
    if(!typedObject)return false;
    Set<ValueType> &  theset = getMutableSetReference(typedObject);
    theset.addObjectObserver(observer);
    return true;
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::removeObserver(Object * ptr,ObjectObserver* observer)const{
    auto object = dynamic_cast<OwningClass*>(ptr);
    if(!object)return false;
    Set<ValueType> &  theset = getMutableSetReference(object);
    theset.removeObjectObserver(observer);
    return true;
  }
  template<typename OwningClass, typename ValueType>
  const Set<ValueType> *  TypedPropertySetInfo<OwningClass,ValueType>::getConstTypedPointer(const OwningClass * object)const{
    return &getConstSetReference(object);
  }
  template<typename OwningClass, typename ValueType>
  Set<ValueType> *  TypedPropertySetInfo<OwningClass,ValueType>::getMutableTypedPointer(OwningClass * object)const{
    return &getMutableSetReference(object);
  }

  template<typename OwningClass, typename ValueType>
  uint  TypedPropertySetInfo<OwningClass,ValueType>::getElementCount(Object * ptr)const{
    auto object = dynamic_cast<OwningClass*>(reinterpret_cast<Object*>(ptr));
    if(!object)return false;
    return getConstSetReference(object).size();
  }

  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::addTypedElement(OwningClass & object, ValueType & value)const{
    return getMutableSetReference(&object).add(value);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::removeTypedElement(OwningClass & object, const ValueType & value)const{
    return getMutableSetReference(&object).remove(value);
  }

  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::addElement(Object * object, void*value)const{
    auto typedObject = dynamic_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<ValueType*>(value);
    return addTypedElement(*typedObject,*typedValue);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::removeElement(Object * object, const void*value)const{
    auto typedObject = dynamic_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<const ValueType*>(value);
    return removeTypedElement(*typedObject,*typedValue);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::setTypedElement(OwningClass * object, uint i, const ValueType * value )const{
    Set<ValueType> & propertyset = getMutableSetReference(object);
    if(i>=propertyset.size())return false;
    return propertyset.setValue(i,*value);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::getTypedElement(const OwningClass * object, uint i, ValueType * value )const{
    const Set<ValueType> & propertyset = getConstSetReference(object);
    if(i>=propertyset.size())return false;
    return propertyset.getValue(i,*value);
  }
  template<typename OwningClass, typename ValueType>
  // sets the value of the property set at i
  bool  TypedPropertySetInfo<OwningClass,ValueType>::setElement(Object * object, uint i, const void * value)const{
    auto typedObject = dynamic_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<const ValueType*>(value);
    if(!typedObject)return false;
    return setTypedElement(typedObject,i,typedValue);
  }
  // gets the value of the property set at i
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::getElement(const Object * object, uint i, void * value)const{
    auto typedObject = dynamic_cast<const OwningClass*>(object);
    auto typedValue = reinterpret_cast<ValueType*>(value);
    if(!typedObject)return false;
    return getTypedElement(typedObject,i,typedValue);
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::deserializeElement(Object * object, uint i, std::istream & in)const{
    OwningClass * owningClass = dynamic_cast<OwningClass*>(object);
    if(!owningClass)return false;
    ValueType value;
    if(getCustomDeserializer()){
      if(!(getCustomDeserializer()->deserialize(&value,in)))return false;
    }else{
      if(!Deserializer<ValueType>::deserialize(&value,in))return false;
    }

    setTypedElement(owningClass,i,&value);
    return true;
  }
  template<typename OwningClass, typename ValueType>
  bool  TypedPropertySetInfo<OwningClass,ValueType>::serializeElement(Object * object,uint i,  std::ostream & out)const{
    OwningClass * owningClass = dynamic_cast<OwningClass*>(object);
    if(!owningClass)return false;
    ValueType value;
    getTypedElement(owningClass,i,&value);
    if(getCustomSerializer()){
      if(!(getCustomSerializer()->serialize(out,&value)))return false;
    }else{
      if(!Serializer<ValueType>::serialize(out,&value))return false;
    }
    return true;
  }
}