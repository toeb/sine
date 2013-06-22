#pragma once

#include <core.serialization/Serializer.h>

namespace nspace{
  namespace core{
    namespace serialization{
      // serializes and argument to a value
      class JsonSerializer:public Serializer{
        reflect_type(JsonSerializer);
        reflect_superclasses(Serializer);
      public:
        JsonSerializer();
      protected:
        virtual bool doSerialization(std::ostream & stream, const Argument & value);
      };
    }
  }
}