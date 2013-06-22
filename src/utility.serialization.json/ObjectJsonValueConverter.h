#pragma once
#include <utility.serialization.json/JsonValueConverter.h>

namespace nspace{
  namespace core{
    namespace serialization{
      // converts any object /  shared_ptr to an Json Value
      // later it will also convert pointer and references
      struct ObjectJsonValueConverter : JsonValueConverter{
        bool canConvert(const Argument & value)const override;
        virtual Json::Value convert(const Argument & argument,SerializationContext & context)const;
      };
    }
  }
}