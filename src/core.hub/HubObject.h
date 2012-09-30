#pragma once
#include <core/Object.h>
#include <core.hub/Hub.h>
namespace nspace{
 class HubObject : public virtual Object{
    TYPED_OBJECT;
  private:
    Hub * _hub;
  public:
    HubObject():_hub(0){}
    const Hub * hub()const{return _hub;}
    Hub * hub(){return _hub;}
    void setHub(Hub * hub){_hub=hub;}
    virtual void onHubSet(Hub * hbu){}
    friend class Hub;
  };

}