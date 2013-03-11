#include <core.reflection/dynamic/DynamicCallable.h>

namespace nspace{
  
  //
  struct DynamicCallableImplementation : public Callable{
    virtual bool isValid()const=0;
    virtual Argument callImplementation(const Arguments &args)=0;
  };
}