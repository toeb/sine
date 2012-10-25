#pragma once
#include <core/Object.h>
namespace nspace{
  class Property : public virtual Object{
    TYPED_OBJECT(Property);

    SIMPLE_PROPERTY(std::string, PropertyName){if(getPropertyDisplayName()!="")return; setPropertyDisplayName(newvalue);}
    SIMPLE_PROPERTY(std::string, PropertyDescription){}
    SIMPLE_PROPERTY(std::string, PropertyDisplayName){}
    SIMPLE_PROPERTY(const TypeData *, PropertyType){}
    SIMPLE_PROPERTY(const void *, DefaultValue){}
    SIMPLE_PROPERTY(std::string, GroupName){}

    REFERENCE_PROPERTY(std::string, PropertyName);
  public:
    // sets this property to the default value
    void setToDefaultValue(void * object)const{setValue(object,getDefaultValue());}
    virtual void setValue(void * object, const void * value)const=0;
    virtual void getValue(const void * object, void * value)const=0;  


    virtual bool deserialize(void * object, std::istream & in)const{return false;}
    virtual bool serialize(void * object, std::ostream & out)const{return false;}

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
