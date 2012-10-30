#include "PropertyAdapter.h"

using namespace nspace;

const Property & PropertyAdapter::property()const{
  return _property;
}
Object * PropertyAdapter::object(){return _object;}

PropertyAdapter::PropertyAdapter(Object * object,const Property & prop):_object(object),_property(prop){

}


void PropertyAdapter::deserialize(std::istream & in){
  this->_property.deserialize(_object,in);
}
void PropertyAdapter::serialize(std::ostream & out){
  this->_property.serialize(object(),out);
}

void PropertyAdapter::setToDefault(){
  this->_property.setToDefaultValue(object());
}