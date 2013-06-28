#pragma once
#include <core.reflection/value/IReadableValue.h>
namespace nspace{
  class IModifiableValue : public IReadableValue{
    reflect_type_declaration(nspace::IModifiableValue);
  private:
    bool changeValue(Argument argument);
  protected:
    virtual bool storeValue(Argument value)=0;
    virtual void valueChanging(Argument newValue, bool & cancel){}
  public:
    IModifiableValue();
    IModifiableValue(const Type * valueType);
    bool set(Argument argument);

    template<typename T>
    void operator =(T  value){
      set(value);
    }



  };
}