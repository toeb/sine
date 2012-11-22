#include "PropertyAdapter.h"

using namespace nspace;

void PropertyAdapter::onBeforeOwnerChanged(){
    uninstallObserver();
}
void PropertyAdapter::onOwnerChanged(){
    installObserver();
}
void PropertyAdapter::onPropertyInfoChanged(){
    installObserver();
    if(!getPropertyInfo())return ;
    setValueType(getPropertyInfo()->getPropertyType());
}
void PropertyAdapter::onChange(Observable * observable){
    raiseObjectChanged();
}
void PropertyAdapter::onBeforePropertyInfoChanged(){
    uninstallObserver();
}
void PropertyAdapter::installObserver(){
    if(!getPropertyInfo())return;
    if(!getOwner())return;
    bool result = getPropertyInfo()->addObserver(getOwner(),this);

}
void PropertyAdapter::uninstallObserver(){
    if(!getPropertyInfo())return;
    if(!getOwner())return;
    bool result = getPropertyInfo()->removeObserver(getOwner(),this);
}

void PropertyAdapter::setToDefault(){
    auto object = getOwner();
    if(!object)return;
    auto info  =getPropertyInfo();
    if(!info)return;
    info->setToDefaultValue(object);
}
PropertyAdapter::~PropertyAdapter(){
  uninstallObserver();
}
PropertyAdapter:: PropertyAdapter():_PropertyInfo(0){


}
PropertyAdapter::PropertyAdapter(Object * object, const std::string & name):_PropertyInfo(0){
    setOwner(object);
    auto prop = object->getType().getProperty(name);
    if(prop)setPropertyInfo(prop);
}
PropertyAdapter::PropertyAdapter(Object * object, const PropertyInfo * info):_PropertyInfo(0){
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
bool PropertyAdapter::storeValue(const void * value){
    auto info = getPropertyInfo();
    auto object = getOwner();
    if(!info)return false;
    if(!object)return false;
    info->setValue(object,value);
    return true;
}
bool PropertyAdapter::toStream(std::ostream & stream, Format format){
    auto info = getPropertyInfo();
    auto object = getOwner();
    if(!info)return false;
    if(!object)return false;
    if(format!=0)return false;
    return info->serialize(object,stream);
}
bool PropertyAdapter::fromStream(std::istream & stream, Format format){
    auto info = getPropertyInfo();
    auto object = getOwner();
    if(!info)return false;
    if(!object)return false;
    if(format!=0)return false;
    return info->deserialize(object,stream);
}
