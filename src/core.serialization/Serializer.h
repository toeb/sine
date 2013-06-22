#pragma once
#include <utility.reader/Writer.h>
namespace nspace{
  namespace core{
    namespace serialization{      
      class Serializer/* :Writer*/{
        reflect_type(Serializer);
      public:    
        std::string serialize(const Argument & value);
        bool serialize(std::ostream & stream, const Argument & value);
      protected:
        virtual bool doSerialization(std::ostream & stream, const Argument & value)=0;
      };
    }
  }
}