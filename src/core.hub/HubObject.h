#pragma once
#include <core/Object.h>
#include <core.hub/Hub.h>
#include <core.graph/DataNode.h>
namespace nspace{
  class HubObject : public virtual Object{
    TYPED_OBJECT(HubObject);
  private:
    friend class Hub;
    friend class CompositeHubObject;
    Set<Hub*> _hubs;
  public:
    HubObject();
    ~HubObject();
    const Set<Hub*> & hubs()const;
  protected:
    virtual void onAddedToHub(Hub & hub){}
    virtual void onRemovedFromHub(Hub & hub){}
  };
}