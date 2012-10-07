#pragma once

#include <core/Object.h>
#include <core/Set.h>

// may only be used inside class which has the a raisePropertyChanged(string) method
#define NOTIFYING_PROPERTY(TYPE, NAME) EXTENDED_PROPERTY(public,TYPE, NAME,{},{static std::string propertyName=#NAME; raisePropertyChanged(propertyName);})


namespace nspace{
  
  
  class PropertyChangingObject;
  class PropertyChangedListener : public virtual Object{
    TYPED_OBJECT(PropertyChangedListener);
  protected:
    virtual void onPropertyChanged(Object * sender, const std::string & propertyName)=0;
    friend class PropertyChangingObject;
  };

  class DelegatePropertyChangedListener : public virtual PropertyChangedListener{
    TYPED_OBJECT(DelegatePropertyChangedListener);
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
    TYPED_OBJECT(PropertyChangingObject);
  private:
    Set<PropertyChangedListener*> _listeners;
  public:
    Set<PropertyChangedListener*> & listeners();
  protected:
    void raisePropertyChanged(const std::string & propertyname);
    virtual void onPropertyChanged(const std::string & propertyname);
  };

}