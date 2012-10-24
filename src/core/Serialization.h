#pragma once

#include <string>
#include <config.h>
namespace nspace{
  // serializers need to use pointers else auto conversion would disrupt everything
  template<typename T>
  class Deserializer{
  public:
    static bool deserialize(T * result, std::istream & in){return false;}
  };
  template<typename T>
  class Serializer{
  public:
    static bool serialize(std::ostream & out, const T * in){
      out << *in;
      return true;
    }
  };

// this macro is a shorthand for specialization of Serializer and Deserializer class
#define SERIALIZERS(TYPE,SERIALIZE,DESERIALIZE)\
  template<>\
  class Deserializer<TYPE>{\
  public:\
    static bool deserialize(TYPE * value, std::istream & stream){DESERIALIZE;return true;}\
  };\
  template<>\
  class Serializer<TYPE>{\
  public:\
    static bool serialize(std::ostream & stream,const TYPE* value){SERIALIZE;return true;}\
  };

  
// this macro allows easy creation of serializes based on the stream operator << and >>
#define DEFAULTSERIALIZERS(TYPE) SERIALIZERS(TYPE,stream<<*value;return true;,stream>>*value;return true;)
  
DEFAULTSERIALIZERS(int);
DEFAULTSERIALIZERS(unsigned int);
DEFAULTSERIALIZERS(double);
DEFAULTSERIALIZERS(float);
DEFAULTSERIALIZERS(bool);
SERIALIZERS(std::string,
{stream << *value;}
, 
{
  //read stream to end
  std::istreambuf_iterator<char> eos;
  std::string s(std::istreambuf_iterator<char>(stream), eos);
  *value = s;
});

}