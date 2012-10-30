#pragma once

#include <core/Property.h>
namespace nspace{
  
  class PropertyAdapter : public Object{
  private:
    Object * _object;
    const Property & _property;
  public:
    const Property & property()const;
    Object * object();

    PropertyAdapter(Object * object,const Property & prop);
    
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

    void deserialize(std::istream & in);
    void serialize(std::ostream & out);

    void setToDefault();
  };
}