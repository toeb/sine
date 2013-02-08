#pragma once

#include <core/Object.h>

namespace nspace{
  class ISerializeable:public virtual Object{
    DS_CLASS(ISerializeable);
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