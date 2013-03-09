#pragma once
#include <core.reflection/value/IReadableValue.h>
namespace nspace{
  class IModifiableValue : public IReadableValue{
    TYPED_OBJECT(IModifiableValue);
  private:
    bool changeValue(Argument argument);
  protected:
    virtual bool storeValue(Argument value)=0;
    virtual void valueChanging(Argument newValue, bool & cancel){}
  public:
    bool set(Argument argument);
  };
}