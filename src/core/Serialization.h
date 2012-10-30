#pragma once

#include <string>
#include <config.h>
#include <core/Set.h>
#include <sstream>
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




  template<typename T>
  std::string serializeString(const T & value){
    static std::string defaultString ="";
    std::stringstream ss;
    if(!Serializer<T>::serialize(ss,&value))return defaultString;
    return ss.str();
  }
  template<typename T>
  bool deserializeString(T & value, const std::string& serialized){
    std::stringstream ss(serialized);
    return Deserializer<T>::deserialize(&value,ss);

  }

  
  
  class CustomSerializer{
  public:
    virtual bool serialize(std::ostream & o, const void * value)=0;
  };
  class CustomDeserializer{
  public:
    virtual bool deserialize( void * value,std::istream & o)=0;
  };
  template<typename T>
  class TypedCustomSerializer :public virtual CustomSerializer{
  public:
    bool serialize(std::ostream & o, const void * value){return serializeType(o,reinterpret_cast<const T*>(value));}
    virtual bool serializeType(std::ostream & o,const T* value)=0;
  };
  template<typename T>
  class TypedCustomDeserializer:public virtual CustomDeserializer{
  public:
    bool deserialize( void * value,std::istream & i){return deserializeType(reinterpret_cast<T*>(value),i);}
    virtual bool deserializeType(T*value, std::istream & i)=0;
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
SERIALIZERS(bool,{
 if(*value)stream << "true";
 else stream << "false";
 


} ,{
   std::string s;
 stream >> s;
  if(s=="true"||s=="1"||s=="yes"||s=="on"){
    *value = true;
    return true;
  }else if(s=="false"||s==""||s=="no"||s=="off"||s=="0"){
    *value = false;
    return true;
  }
  return false;

});
SERIALIZERS(std::string,
{stream << *value;}
, 
{
  //read stream to end
  std::istreambuf_iterator<char> eos;
  std::string s(std::istreambuf_iterator<char>(stream), eos);
  *value = s;
});





// set serializers
template <typename T>
class Serializer<Set<T> >{
public:
  static bool serialize(std::ostream & stream, const Set<T> * value){  
    const Set<T> & val = *value;
    for(int i=0; i< val; i++){    
      T v = val.at(i);
      if(!Serializer<T>::serialize(stream,&v)){
        stream << "{"<<i<<"}";
      }
      if(i<val.size()-1)stream<<", ";
    }
    return true;
  };
};

// set serializers
template <typename T>
class Deserializer<Set<T> >{
public:
  static bool deserialize(Set<T> * value, std::istream & stream){
    Set<T> tmp;
    char c= stream.peek();
    switch(c){
    case '|':
    case '&':
    case '^':
    case '=':
      stream >> c;
      break;
    default:      
      c = '=';

    }
    while(stream){
      T i;
      if(!Deserializer<T>::deserialize(&i,stream)){
        // if any element could not be serialized
        return false;
      }
      tmp|=i;
    }

    switch(c){
    case '|':
    *value |= tmp;
      break;
    case '&':
    *value &= tmp;
      break;
    case '^':
    *value ^= tmp;
      break;
    case '=':      
    default:
    *value = tmp;
      break;
    }

    return true;
  }
};


}
