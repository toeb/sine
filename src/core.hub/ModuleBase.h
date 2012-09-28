#pragma once

#include <core.hub/Module.h>

namespace nspace{
class ModuleBase : public virtual Module{
    TYPED_OBJECT;
  private:
    Set<Object*> _objects;
  public:
    const Set<Object*> objects(){return _objects;}
    virtual bool accept(Object * object)=0;

    virtual void onAcception(Object * object){}
    virtual void onRejection(Object * object){}
    virtual void onAnnounce(Object * object){}
    virtual void onRenounce(Object * object){}
    virtual void onBeforeRenounce(Object * object){}

    void announce(Object * object){
      onAnnounce(object);
      if(accept(object)){
        _objects |= object;
        onAcception(object);
      }else{
        onRejection(object);
      }     
    }
    void renounce(Object * object){
      if(_objects.contains(object)){
        onBeforeRenounce(object);
      }
      if(_objects.remove(object)){
        onRenounce(object);
      }
    }

  };

}