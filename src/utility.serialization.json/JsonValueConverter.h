#pragma once

#include <core.reflection.h>
#include <core.serialization/SerializationContext.h>
#include <json/json.h>
namespace nspace{
  namespace core{
    namespace serialization{
      // a class which allows converting an argument to a Json::Value
      struct JsonValueConverter{
        // static method returns a value converter which can convert value or returns 0
        static const JsonValueConverter * Get(const Argument & value);
        // returns the list of instanciated converters
        static std::vector<const JsonValueConverter*> & Converters();
        // default constructor
        JsonValueConverter();
        // subclasses return true if it can convert argument
        virtual bool canConvert(const Argument & argument)const=0;
        // subclasses return the converted value of argument, using serialization context
        virtual Json::Value convert(const Argument & argument,SerializationContext & context)const=0;
      };
    }
  }
}

