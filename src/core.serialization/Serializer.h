#pragma once
#include <core.reflection.h>
#include <core.serialization/Serialization.h>
#include <core.serialization/SerializationContext.h>
namespace nspace{
  namespace core{
    namespace serialization{      
      class Serializer{
        reflect_type(Serializer);
        typedef SerializationFormat reflect_property(Format);
        
      protected:
        Serializer(const SerializationFormat & format);
        virtual bool doSerialization(std::ostream & stream, const Argument & value, SerializationContext & context)const=0;
      public:    
        std::string serialize(const Argument & value)const;
        bool serialize(std::ostream & stream, const Argument & value)const;
      };
    }
  }
}