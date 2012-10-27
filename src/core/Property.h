#pragma once
#include <core/Object.h>
namespace nspace{

  
  class CustomSerializer{
  public:
    virtual bool serialize(std::ostream & o, const void * value)=0;
  };
  class CustomDeserializer{
  public:
    virtual bool deserialize( void * value,std::istream & o)=0;
  };
  template<typename T>
  class TypedCustomSerializer :public virtual CustomSerializer{
  public:
    bool serialize(std::ostream & o, const void * value){return serializeType(o,reinterpret_cast<const T*>(value));}
    virtual bool serializeType(std::ostream & o,const T* value)=0;
  };
  template<typename T>
  class TypedCustomDeserializer:public virtual CustomDeserializer{
  public:
    bool deserialize( void * value,std::istream & i){return deserializeType(reinterpret_cast<T*>(value),i);}
    virtual bool deserializeType(T*value, std::istream & i)=0;
  };


  class Property : public virtual Object{
    TYPED_OBJECT(Property);

    SIMPLE_PROPERTY(std::string, PropertyName){if(getPropertyDisplayName()!="")return; setPropertyDisplayName(newvalue);}
    
    SIMPLE_PROPERTY(std::string, PropertyDescription){}
    SIMPLE_PROPERTY(std::string, PropertyDisplayName){}
    SIMPLE_PROPERTY(std::string, GroupName){}
    SIMPLE_PROPERTY(bool, IsVisible){}
    
    SIMPLE_PROPERTY(bool, HasGetter){}
    SIMPLE_PROPERTY(bool, HasSetter){}
    SIMPLE_PROPERTY(bool, HasConstReference){}
    SIMPLE_PROPERTY(bool, HasMutableReference){}


    // the typedata of the property
    SIMPLE_PROPERTY(const TypeData *, PropertyType){}
    // access to the default value
    SIMPLE_PROPERTY(const void *, DefaultValue){}
    // custom serializer
    SIMPLE_PROPERTY(CustomSerializer*, CustomSerializer){}
    // custom deserializer
    SIMPLE_PROPERTY(CustomDeserializer*, CustomDeserializer){}
    

    REFERENCE_PROPERTY(std::string, PropertyName);
  public:
    Property():
      _PropertyType(0),
      _DefaultValue(0),
      _CustomDeserializer(0),
      _CustomSerializer(0),
      _IsVisible(true),
      _HasGetter(false),
      _HasSetter(false),
      _HasMutableReference(false),
      _HasConstReference(false)
    {}
    // sets this property to the default value
    void setToDefaultValue(void * object)const{setValue(object,getDefaultValue());}
    // sets the value of the property
    virtual void setValue(void * object, const void * value)const=0;
    // gets the value of the property
    virtual void getValue(const void * object, void * value)const=0;  

    virtual void * getMutableReference()const{return 0;}
    virtual const void * getConstReference()const{return 0;}
    
    virtual bool deserialize(void * object, std::istream & in)const=0;
    virtual bool serialize(void * object, std::ostream & out)const=0;

    template<typename ObjectType, typename T>
    void get(T& value, const ObjectType & object)const{
      getValue(&object,&value);
    }
    template<typename ObjectType, typename T>
    void set(const T& value, ObjectType & object)const{
      setValue(&object,&value);
    }    
  };

  class PropertyAdapter{
  private:
    void * _object;
    const Property & _property;
  public:
    const Property & property()const{
      return _property;
    }
    void * object(){return _object;}

    PropertyAdapter(void * object,const Property & prop):_object(object),_property(prop){

    }
    
    template< typename T>
    void get(T& value){
      this-> _property.getValue(object(),&value);
    }
    template< typename T>
    T get(){
      T t;
      this->_property.getValue(object(),&t);
      return t;
    }
    template< typename T>
    void set(const T& value){
      this->_property.setValue(object(),&value);
    }

    void deserialize(std::istream & in){
      this->_property.deserialize(_object,in);
    }
    void serialize(std::ostream & out){
      this->_property.serialize(object(),out);
    }

    void setToDefault(){
      this->_property.setToDefaultValue(object());
    }
  };
}
