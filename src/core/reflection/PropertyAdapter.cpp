#include "PropertyAdapter.h"

using namespace nspace;


void PropertyAdapter::setToDefault(){
  auto object = getOwner();
  if(!object)return;
  auto info  =getPropertyInfo();
  if(!info)return;
  info->setToDefaultValue(object);
}

void PropertyAdapter::propertyChanging(const PropertyInfo *, PropertyInfo){
  setValueType(newvalue->getPropertyType());
}
PropertyAdapter:: PropertyAdapter():_PropertyInfo(0){

}
PropertyAdapter::PropertyAdapter(Object * object, const std::string & name){
  setOwner(object);
  auto prop = object->getType().getProperty(name);
  if(prop)setPropertyInfo(prop);
}
PropertyAdapter::PropertyAdapter(Object * object, const PropertyInfo * info){
  setOwner(object);
  setPropertyInfo(info);
}
bool PropertyAdapter::retrieveValue(void * value)const{
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object)return false;
  info->getValue(object,value);
  return true;
}
bool PropertyAdapter:: storeValue(const void * value){
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object)return false;
  info->setValue(object,value);
}
bool PropertyAdapter::toStream(std::ostream & stream, Format format){
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object)return false;
  if(format!=0)return false;
  info->serialize(object,stream);
}
bool PropertyAdapter::fromStream(std::istream & stream, Format format){
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object)return false;
  if(format!=0)return false;
  info->deserialize(object,stream);
}