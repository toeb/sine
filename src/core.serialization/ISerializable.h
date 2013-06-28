#pragma once
#include <core.reflection.h>

namespace nspace{
  class ISerializeable{
    DS_CLASS(nspace::ISerializeable);
  public:
    typedef uint Format;
  protected:
    virtual bool toStream(std::ostream & stream, Format format);
    virtual bool fromStream(std::istream & stream, Format format);
    virtual void onSerialized();
    virtual void onDeserialized();
  public:
    bool serialize(std::ostream & stream, Format format=0);
    bool deserialize(std::istream & stream, Format format=0);
  };
}