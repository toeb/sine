#pragma once

#include <core/Object.h>
namespace nspace{
 // a module is a object which is notified whenever an object is added or removed
  // the name might need some changing
  class Module : public virtual Object{
    TYPED_OBJECT(Module);
  public:
    virtual void announce(Object * object)=0;
    virtual void renounce(Object * object)=0;
  };
}