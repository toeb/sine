#pragma once

#include <core.serialization/Deserializer.h>

namespace nspace{
  namespace core{
    namespace serialization{

      class JsonDeserializer : public Deserializer{
        reflect_type(JsonDeserializer);
        reflect_superclasses(Deserializer);
      public:
        reflected_default_constructor(public:JsonDeserializer);
      protected:
        Argument doDeserialization(std::istream & stream ,const Type*type, DeserializationContext & context)const override;
      };
    }
  }
}