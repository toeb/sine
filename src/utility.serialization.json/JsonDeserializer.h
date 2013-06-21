#pragma once

#include <core.serialization/Deserializer.h>

namespace nspace{
  namespace core{
    namespace serialization{

      class JsonDeserializer : public Deserializer{
      protected:
        Argument doDeserialization(std::istream & stream)override;
      };
    }
  }
}