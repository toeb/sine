#pragma once
#include <core/Property.h>
#include <core/Serialization.h>
namespace nspace{

  template<typename OwningClass, typename ValueType>
  class TypedProperty : public virtual Property{
    TYPED_OBJECT(TypedProperty);
  public:
    TypedProperty(){
      setPropertyType(&TypeDataProvider<ValueType>::getTypeData());
    }
  private:

    const void * getConstReference()const{return reinterpret_cast<const void*>(getConstTypedReference());}
    void * getMutableReference()const{return reinterpret_cast<void*>( getMutableTypedReference());}

    virtual const ValueType * getConstTypedReference()const{return 0;}
    virtual ValueType * getMutableTypedReference()const{return 0;}


    
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
    virtual bool deserialize(void * ptr, std::istream & in)const{
      // get Object* from ptr
      Object *object = reinterpret_cast<Object*>(ptr);
      OwningClass * owningClass = dynamic_cast<OwningClass*>(object);
      if(!owningClass)return false;
      ValueType value;
      if(getCustomDeserializer()){
         if(!(getCustomDeserializer()->deserialize(&value,in)))return false;
      }else{
        if(!Deserializer<ValueType>::deserialize(&value,in))return false;
      }

      setTypedValue(owningClass,value);
      return true;
    }
    virtual bool serialize(void * object, std::ostream & out)const{
      OwningClass * owningClass = dynamic_cast<OwningClass*>(static_cast<Object*>(object));
      ValueType value = getTypedValue(owningClass);
      if(getCustomSerializer()){
         if(!(getCustomSerializer()->serialize(out,&value)))return false;
      }else{
        if(!Serializer<ValueType>::serialize(out,&value))return false;
      }
      return true;
    }
    virtual void setTypedValue(OwningClass *  object , ValueType value)const=0;
    virtual ValueType getTypedValue(const OwningClass *  object)const=0;
  };
}
