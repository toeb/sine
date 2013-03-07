#include "PropertyAdapter.h"

using namespace nspace;

void PropertyAdapter::onBeforeOwnerChanged(){
}
void PropertyAdapter::onOwnerChanged(){
}
void PropertyAdapter::onPropertyInfoChanged(){
  if(!getPropertyInfo())return ;
  setValueType(getPropertyInfo()->getPropertyType());
}
void PropertyAdapter::onChange(Observable * observable){
  raiseObjectChanged();
}
void PropertyAdapter::onBeforePropertyInfoChanged(){
}
/*
void PropertyAdapter::setToDefault(){
  auto object = getOwner();
  if(!object.isValid())return;
  auto info  =getPropertyInfo();
  if(!info)return;
  info->setToDefaultValue(object);
}*/
PropertyAdapter::~PropertyAdapter(){
}
PropertyAdapter:: PropertyAdapter():_PropertyInfo(0){
}
PropertyAdapter::PropertyAdapter(Argument object, const std::string & name):_PropertyInfo(0){
  setOwner(object);
  auto prop = object.type->getProperty(name);
  if(prop)setPropertyInfo(prop);
}
PropertyAdapter::PropertyAdapter(Argument object, const PropertyInfo * info):_PropertyInfo(0){
  setOwner(object);
  setPropertyInfo(info);
}
Argument PropertyAdapter::retrieveValue()const{
 return getPropertyInfo()->get(getOwner().data.get());
}
bool PropertyAdapter::storeValue(Argument argument){
  getPropertyInfo()->set(getOwner().data.get(),argument);
  return true;
}
/*
bool PropertyAdapter::retrieveValue(void * value)const{
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object.isValid())return false;
  info->getValue(object,value);
  return true;
}
bool PropertyAdapter::storeValue(const void * value){
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object.isValid())return false;
  info->setValue(object,value);
  return true;
}
bool PropertyAdapter::toStream(std::ostream & stream, Format format){
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object.isValid())return false;
  if(format!=0)return false;
  return info->serialize(object,stream);
}
bool PropertyAdapter::fromStream(std::istream & stream, Format format){
  auto info = getPropertyInfo();
  auto object = getOwner();
  if(!info)return false;
  if(!object.isValid())return false;
  if(format!=0)return false;
  return info->deserialize(object,stream);
}*/