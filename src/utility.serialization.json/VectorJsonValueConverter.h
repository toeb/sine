#pragma once

#include <utility.serialization.json/JsonValueConverter.h>

namespace nspace{
  namespace core{
    namespace serialization{
      // converts a vector of any template type to a json value array
      struct VectorJsonValueConverter: public JsonValueConverter{
        virtual bool canConvert(const Argument & argument)const override ;
        virtual Json::Value convert(const Argument & value, SerializationContext & context)const override ;
      };
    }
  }
}