#pragma once
#include <core/Object.h>
#include <core/Serialization.h>
#include <core/MemberInfo.h>
namespace nspace{


  class Property : public virtual MemberInfo{
    TYPED_OBJECT(Property);
    SUBCLASSOF(MemberInfo);    
    SIMPLE_PROPERTY(bool, HasGetter){}
    SIMPLE_PROPERTY(bool, HasSetter){}
    // the typedata of the property
    SIMPLE_PROPERTY(const TypeData *, PropertyClass){}
    // access to the default value
    SIMPLE_PROPERTY(const void *, DefaultValue){}
    // custom serializer
    SIMPLE_PROPERTY(CustomSerializer*, CustomSerializer){}
    // custom deserializer
    SIMPLE_PROPERTY(CustomDeserializer*, CustomDeserializer){}
    BASIC_PROPERTY(std::function<Object* (void *)>, ObjectConverter,public,,,);
    SIMPLE_PROPERTY(bool, IsNavigatable){}
    SIMPLE_PROPERTY(bool, IsPointer){}
    SIMPLE_PROPERTY(bool, IsVisible){}
  public:
    Property():
      _HasGetter(false),
      _HasSetter(false),
      _PropertyClass(0),
      _DefaultValue(0),
      _CustomSerializer(0),
      _CustomDeserializer(0),
      _ObjectConverter([](void * ptr){return static_cast<Object*>(0);}),
      _IsNavigatable(false),
      _IsPointer(false),
      _IsVisible(true)
    {}


    // sets this property to the default value
    void setToDefaultValue(Object * object)const{setValue(object,getDefaultValue());}
    // sets the value of the property
    virtual void setValue(Object * object, const void * value)const=0;
    // gets the value of the property
    virtual void getValue(const Object * object, void * value)const=0;  
    // if the value is a pointer and a subtype of object this method returns the pointer as an Object
    Object * asObjectPointer(const Object * object)const{  
      if(!getIsPointer())return 0;
      void * value;
      getValue(object,&value); 
      return getObjectConverter()(value); 
    }

    virtual void * getMutablePointer(Object * object)const{return 0;}
    virtual const void * getConstPointer(const Object * object)const{return 0;}
    
    virtual bool deserialize(Object * object, std::istream & in)const=0;
    virtual bool serialize(Object * object, std::ostream & out)const=0;

    
    virtual bool addObserver(Object * object,ObjectObserver* observer)const{return false;};
    virtual bool removeObserver(Object * object,ObjectObserver* observer)const{return false;};


    template<typename ObjectType, typename T>
    void get(T& value, const ObjectType & object)const{
      getValue(&object,&value);
    }
    template<typename ObjectType, typename T>
    void set(const T& value, ObjectType & object)const{
      setValue(&object,&value);
    }    
  };

}
