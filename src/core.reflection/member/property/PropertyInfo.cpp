#include "PropertyInfo.h"

#include <core/PropertyChangingObject.h>
using namespace std;
using namespace nspace;
/*
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

bool PropertyInfo::addObserver(Object * object,ObjectObserver* observer)const{
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
};*/