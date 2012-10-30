#pragma once
#include <core/Property.h>

namespace nspace{
  // describes a class property which is a set /collection
  class PropertySetInfo : public virtual Object, public virtual Property{  
    TYPED_OBJECT(PropertySetInfo);

    SIMPLE_PROPERTY(const TypeData*, ElementType){}

    // custom serializer
    SIMPLE_PROPERTY(CustomSerializer*, CustomElementSerializer){}
    // custom deserializer
    SIMPLE_PROPERTY(CustomDeserializer*, CustomElementDeserializer){}
    SIMPLE_PROPERTY(bool, IsPointerCollection){}
    
    BASIC_PROPERTY(std::function<Object* (void *)>, ElementToObjectConverter,public,,,);
  public:
    PropertySetInfo():
      _ElementType(0),
      _CustomElementDeserializer(0),
      _CustomElementSerializer(0),
      _IsPointerCollection(false),
      _ElementToObjectConverter([](void * ptr){return static_cast<Object*>(0);})
    {}
    // sets the value of the property set at i
    virtual bool setElement(Object * object, uint i, const void * value)const=0;
    // gets the value of the property set at i
    virtual bool getElement(const Object * object, uint i, void * value)const=0;  

    Object * elementAsObjectPointer(Object * object, uint i)const{
      if(!getIsPointerCollection())return 0;
      void * value;
      if(!getElement(object,i,&value))return 0;
      return getElementToObjectConverter()(value);
    }

    virtual bool addElement(Object * object, void*value)const=0;
    virtual bool removeElement(Object * object, const void*value)const=0;

    virtual bool deserializeElement(Object * object, uint i,std::istream & in)const=0;
    virtual bool serializeElement(Object * object, uint i,std::ostream & out)const=0;
    

    virtual uint getElementCount(Object * object)const=0;

    template<typename ObjectType, typename T> bool get(T& value, uint i, const ObjectType & object)const{ getValue(&object,i,&value); }
    template<typename ObjectType, typename T> bool set(const T& value, uint i, ObjectType & object)const{ setValue(&object,i,&value); }   


  };
}