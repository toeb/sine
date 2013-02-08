#include "PropertyChangingObject.h"

#include <core.reflection/type/TypeInfo.h>
using namespace nspace;

DS_CLASS_DEFINITION(PropertyChangedListener);
DS_CLASS_DEFINITION(DelegatePropertyChangedListener);
DS_CLASS_DEFINITION(PropertyChangingObject);

Set<PropertyChangedListener*> & PropertyChangingObject::listeners(){return _listeners;}

void PropertyChangingObject::raisePropertyChanged(const std::string & propertyname){
  onPropertyChanged(propertyname);
  _listeners.foreachElement([this, &propertyname](PropertyChangedListener* listener){
    listener->onPropertyChanged(this,propertyname);
  });
}
void PropertyChangingObject::onPropertyChanged(const std::string & propertyname){}