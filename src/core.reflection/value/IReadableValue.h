#pragma once

#include <core/Object.h>
#include <core/Observable.h>
#include <core.property.h>
#include <core.reflection/type/TypeInfo.h>

#include <core.reflection/type/Argument.h>

namespace nspace{
  class IReadableValue : public Observable{
    reflect_type(IReadableValue);    
   typedef const Type * basic_property(ValueType);
  protected:
    virtual Argument retrieveValue()const=0;
  public:
    IReadableValue();
    IReadableValue(const Type * valueType);
    Argument get()const;
  };
}
