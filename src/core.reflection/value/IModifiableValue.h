#pragma once
#include <core/reflection/IReadableValue.h>
namespace nspace{
  class IModifiableValue : public IReadableValue{
    TYPED_OBJECT(IModifiableValue);
  private:
    bool changeValue(const void * value);
  protected:
    virtual bool storeValue(const void * value)=0;
    virtual void valueChanging(const void * newvalue, bool & cancel){}
  public:
    bool setByPointer(const void * value);
    template<typename T> bool set(const T & value){ return setByPointer(&value); }
  };
}