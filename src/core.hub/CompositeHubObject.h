#pragma once

#include <core.hub/HubObject.h>

#include <core.h>



namespace nspace{


  


  // a CompositeHubObject(cho) manages a a set of components that are added to the hub that this cho belongs to 
  // and are removed from the hub when this cho is removed. this is useful for groups of objects that are only used together
  class CompositeHubObject : public HubObject, public virtual DataNode<Object*>{
    REFLECTABLE_OBJECT(CompositeHubObject);
  private:
    // the difference between components and references is, that components are removed when this composite is removed from the hub
    //whilst the references are not removed.  however both are added to the hub
    PROPERTYSET(Object*, Components,,);
    PROPERTYSET(Object*, References,,);

  public:
    CompositeHubObject();
    ~CompositeHubObject();

  protected:


    virtual void onObjectAdded(Object * object){}
    virtual void onObjectRemoved(Object * object){}
    virtual void onReferenceAdded(Object * object){}
    virtual void onReferenceRemoved(Object * object){}
    virtual void onComponentAdded(Object * object){}
    virtual void onComponentRemoved(Object * object){}


    // the overriding methods should make sure to call these methods
    virtual void onAddedToHub(Hub & hub);
    virtual void onRemovedFromHub(Hub & hub);

  private: 
    void addObject(Object * object);
    void removeObject(Object * object, bool fromHub);

  };


}
