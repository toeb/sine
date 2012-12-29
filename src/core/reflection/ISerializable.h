#pragma once

#include <core/Object.h>

namespace nspace{
  class ISerializeable:public virtual Object{
    TYPED_OBJECT(ISerializeable);
  public:
    typedef uint Format;
  protected:
    virtual bool toStream(std::ostream & stream, Format format){return false;}
    virtual bool fromStream(std::istream & stream, Format format){return false;}
    virtual void onSerialized(){}
    virtual void onDeserialized(){}
  public:
    bool serialize(std::ostream & stream, Format format=0){
      bool success = toStream(stream,format);
      if(success)onSerialized();
      return success;
    }
    bool deserialize(std::istream & stream, Format format=0){
      bool success = fromStream(stream,format);
      if(success)onDeserialized();
      return success;
    }
  };
}