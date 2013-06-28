#pragma once

#include <core/Object.h>
#include <core.collection/containers/Set.h>

// may only be used inside class which has the a raisePropertyChanged(string) method
// a private raise<NAME>Changed() method is created which allows this class to control additionally raise the changed event
// then a public PROPERTY is added
#define NOTIFYING_PROPERTY(TYPE, NAME) \
  private:\
  inline void notify##NAME##Changed(){static std::string propertyName=#NAME; raisePropertyChanged(propertyName);}\
  EXTENDED_PROPERTY(TYPE, NAME,public,,,{notify##NAME##Changed();})





namespace nspace{
  // forward declaration of PropertyChangingObject
  class PropertyChangingObject;

  // A PropertyChangedListener can be added to a PropertyChangingObject and is notified via onPropertyChanged when a property of the Object has Changed
  class PropertyChangedListener : public virtual Object{
    reflect_type(nspace::PropertyChangedListener)
  protected:
    virtual void onPropertyChanged(Object * sender, const std::string & propertyName)=0;
    friend class PropertyChangingObject;
  };

  // an implementation of PropertyChangedListener which will delegate it
  class DelegatePropertyChangedListener : public virtual PropertyChangedListener{
    reflect_type(nspace::DelegatePropertyChangedListener);
  private:
    std::function<void (Object * , const std::string & ) > _callback;
  public:
    DelegatePropertyChangedListener(std::function<void (Object * , const std::string & ) > callback):_callback(callback){
    }
    void onPropertyChanged(Object * sender, const std::string & propertyName){
      _callback(sender,propertyName);
    }
  };
  
  // an object which allows listeners to listen for property change events
  class PropertyChangingObject : public virtual Object{
    reflect_type(nspace::PropertyChangingObject);
  private:
    Set<PropertyChangedListener*> _listeners;
  public:
    Set<PropertyChangedListener*> & listeners();
  protected:
    void onAfterPropertySet(const char * name);
    // handler for extensible_properties
    void raisePropertyChanged(const std::string & propertyname);
    virtual void onPropertyChanged(const std::string & propertyname);
  };
  // declare this macro in a class which uses extensible properties and PropertyChanging object.
  // else one must handle property changes manually
#define notify_property_changed using PropertyChangingObject::onAfterPropertySet;
}