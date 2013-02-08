#pragma once
#include <core/reflection/ISerializable.h>
#include <core/reflection/ITypedModifiableValue.h>
namespace nspace{
  template<typename T>
  class ITypedSerializableValue : public virtual ISerializeable, public virtual ITypedModifiableValue<T>{
    TYPED_OBJECT(ITypedSerializableValue<T>);
  protected:
    virtual bool toStream(std::ostream & stream, Format format){
      if(format!=0)return false;
      T value;
      this->get(value);
      return Serializer<T>::serialize(stream, &value);
    }
    virtual bool fromStream(std::istream & stream, Format format){
      if(format!=0)return false;
      T value;
      if(!this->get(value))return false;
      bool success = Deserializer<T>::deserialize(&value,stream);
      if(!success)return false;
      this->set(value);
      return true;
    }
  };
}
