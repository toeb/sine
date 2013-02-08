#include "PropertyInfo.h"

#include <core/PropertyChangingObject.h>
using namespace std;
using namespace nspace;

/*
void * PropertyInfo::asObjectPointer(const Object * object) const {
if(!getIsPointer()) return 0;
void * value;
getValue(object,&value);
return getObjectConverter() (value);
}*/
/*

auto PropertyInfo::getMutablePointer(void * object) const  -> PropertyInfo::ValuePointer{
return 0;
}

auto PropertyInfo::getConstPointer(void * object) const -> const PropertyInfo::ValuePointer{
return 0;
}
*/

void PropertyInfo::setToDefaultValue(ObjectPointer object) const {
  if(getDefaultValue()){
    auto defaultValue  = getDefaultValue();

    setValue(object,defaultValue);
  }
}

PropertyInfo::PropertyInfo() :
  _HasGetter(false),
  _HasSetter(false),
  _PropertyType(0),
  _DefaultValue(0),
  _CustomSerializer(0),
  _CustomDeserializer(0),
  _ObjectConverter([] (void * ptr){return static_cast<Object*>(0); }),
  _IsNavigatable(false),
  _IsPointer(false),
  _IsVisible(true)
{}


class ObserverAdapter : public virtual PropertyChangedListener, public virtual Observable{
  SIMPLE_PROPERTY(const PropertyInfo * , PropertyInfo){}
public:
  ObserverAdapter(const PropertyInfo * info):_PropertyInfo(0){
    setPropertyInfo(info);
  }
protected:

  virtual void onPropertyChanged(Object * sender, const std::string & propertyName){
    if(!getPropertyInfo())return ;
    if(propertyName!=getPropertyInfo()->getName())return;
    raiseObjectChanged();
  }
};



bool PropertyInfo::addObserver(ObjectPointer object,ObjectObserver* observer)const{
  auto propertyChangingObject = dynamic_cast<PropertyChangingObject*>(object);
  if(!propertyChangingObject)return false;

  ObserverAdapter* adapter= dynamic_cast<ObserverAdapter*>(propertyChangingObject->listeners().first([this](PropertyChangedListener * listener){
    return dynamic_cast<ObserverAdapter*>(listener)!=0&&dynamic_cast<ObserverAdapter*>(listener)->getPropertyInfo()==this;
  }));

  if(!adapter){
    adapter = new ObserverAdapter(this);
    propertyChangingObject->listeners()|=adapter;
  }

  adapter->addObjectObserver(observer);

  return true;
};
bool PropertyInfo::removeObserver(Object * object,ObjectObserver* observer)const{
  auto propertyChangingObject = dynamic_cast<PropertyChangingObject*>(object);
  if(!propertyChangingObject)return false;
  //slow

  ObserverAdapter* adapter= dynamic_cast<ObserverAdapter*>(propertyChangingObject->listeners().first([this](PropertyChangedListener * listener){
    return dynamic_cast<ObserverAdapter*>(listener)!=0&&dynamic_cast<ObserverAdapter*>(listener)->getPropertyInfo()==this;
  }));

  if(!adapter)return false;

  adapter->removeObjectObserver(observer);

  if(!adapter->hasObservers()){
    propertyChangingObject->listeners()/= adapter;
    delete adapter;
    adapter =0;
  }
  return true;
};