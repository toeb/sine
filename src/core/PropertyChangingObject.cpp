#include "PropertyChangingObject.h"

using namespace nspace;

Set<PropertyChangedListener*> & PropertyChangingObject::listeners(){return _listeners;}

void PropertyChangingObject::raisePropertyChanged(const std::string & propertyname){
  onPropertyChanged(propertyname);
  _listeners.foreachElement([this, &propertyname](PropertyChangedListener* listener){
    listener->onPropertyChanged(this,propertyname);
  });
}
void PropertyChangingObject::onPropertyChanged(const std::string & propertyname){}