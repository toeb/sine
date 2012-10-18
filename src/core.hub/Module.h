#pragma once

#include <core/Object.h>
namespace nspace{
 
  class Module : public virtual Object{
    TYPED_OBJECT(Module);
  public:
    virtual void announce(Object * object)=0;
    virtual void renounce(Object * object)=0;

    
  };
}