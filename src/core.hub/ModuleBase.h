#pragma once

#include <core/Set.h>
#include <core.hub/Module.h>

namespace nspace{
  class ModuleBase : public virtual Module{
    TYPED_OBJECT(ModuleBase);
  private:
    Set<Object*> _objects;
  public:
    const Set<Object*>& objects()const;
    virtual bool accept(Object * object)=0;

    virtual void onAcception(Object * object){}
    virtual void onRenounce(Object * object){}
    virtual void onRejection(Object * object){}
    virtual void onAnnounce(Object * object){}
    virtual void onBeforeRenounce(Object * object){}

    void announce(Object * object);
    void renounce(Object * object);

  };

  template<typename T>
  class TypedModuleBase : public virtual ModuleBase, protected virtual Set<T*>{
    virtual bool acceptTypedObject(T * object){return true;}
    bool accept(Object * object){
      auto obj = dynamic_cast<T*>(object);
      if(!obj)return false;
      return acceptTypedObject(obj);
    }
    void onAcception(Object * object){
      *this |= dynamic_cast<T*>(object);
    }
    void onRenounce(Object * object){
      *this /= dynamic_cast<T*>(object);
    }    

  };

}