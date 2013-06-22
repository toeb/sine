#pragma once

#include <core.reflection.h>
#include <core.serialization/Serialization.h>
#include <istream>
#include <core.serialization/DeserializationContext.h>
namespace nspace{
  namespace core{
    namespace serialization{
      class Deserializer{
        reflect_type(Deserializer);
        typedef SerializationFormat reflect_property(Format);
      protected:
        Deserializer(const SerializationFormat & format);
        virtual Argument doDeserialization(std::istream & stream, const Type * type, DeserializationContext & context)const=0;        
      public:
        Argument deserialize(const std::string & str)const;
        Argument deserialize(const std::string & str, const Type* type)const;
        Argument deserialize(std::istream & stream)const;
        Argument deserialize(std::istream & stream,const Type* type)const;
        Argument deserializeFile(const std::string & filename)const;
        Argument deserializeFile(const std::string & filename, const Type* type)const;
      };
    }
  }
}