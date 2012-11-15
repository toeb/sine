#pragma once

#include <core/reflection/PropertyInfo.h>
#include <core/reflection/MethodInfo.h>
namespace nspace{
  class PropertyAdapter : public Object{
  private:
    Object * _object;
    const PropertyInfo & _property;
  public:
    const PropertyInfo & property()const;
    Object * object();

    PropertyAdapter(Object * object,const PropertyInfo & prop);
    
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