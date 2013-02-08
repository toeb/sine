#pragma once
#include <core.reflection/member/property/PropertyInfo.h>

namespace nspace{
  // describes a class property which is a set /collection
  class PropertySetInfo : /*public virtual Object,*/ public virtual PropertyInfo{
    /*TYPED_OBJECT(PropertySetInfo);*/

    SIMPLE_PROPERTY(const Type*, ElementType){}

    // custom serializer
    SIMPLE_PROPERTY(CustomSerializer*, CustomElementSerializer){}
    // custom deserializer
    SIMPLE_PROPERTY(CustomDeserializer*, CustomElementDeserializer){}
    SIMPLE_PROPERTY(bool, IsPointerCollection){}

    //BASIC_PROPERTY(std::function<Object* (void *)>, ElementToObjectConverter,public,,,);
  public:
    typedef void * ElementPointer;
    PropertySetInfo();
    // sets the value of the property set at i
    virtual bool setElement(ObjectPointer object, uint i, const ElementPointer value)const=0;
    // gets the value of the property set at i
    virtual bool getElement(const ObjectPointer object, uint i, ElementPointer value)const=0;

    //Object * elementAsObjectPointer(void * object, uint i)const;

    virtual bool addElement(ObjectPointer object, ElementPointer value)const=0;
    virtual bool removeElement(ObjectPointer object, ElementPointer value)const=0;

    virtual bool deserializeElement(ObjectPointer object, uint i,std::istream & in)const=0;
    virtual bool serializeElement(ObjectPointer object, uint i,std::ostream & out)const=0;

    virtual uint getElementCount(ObjectPointer object)const=0;

    template<typename ObjectType, typename T> bool get(T& value, const uint i, const ObjectType & object)const{ return getValue(&object,i,&value); }
    template<typename T, typename ObjectType> T get(const uint i, const ObjectType & object)const{T value; get(value, i, object); return value;}
    template<typename ObjectType, typename T> bool set(const T& value, const uint i, ObjectType & object)const{ return setValue(&object,i,&value); }
  };
}
