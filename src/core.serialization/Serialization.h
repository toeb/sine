#pragma once

#include <core.reflection.h>


namespace nspace{
  namespace core{
    namespace serialization{
      class Serializer;
      class Deserializer;

      typedef std::string SerializationFormat;      
      typedef std::shared_ptr<Serializer> SerializerType;
      typedef std::shared_ptr<Deserializer> DeserializerType;


      // returns true iff a serializer exists for the speceified format
      bool serializerExists(const SerializationFormat & format);
      // returns the serializer for the specified format
      SerializerType serializerFor(const SerializationFormat & format);
      // returns a list of serializers
      const std::vector<SerializerType> & serializers();
      // serializes the Argument into the output stream using the specified format
      bool serialize(std::ostream  & stream, const Argument & argument, const SerializationFormat  & format);
      bool serialize(const std::string & str, const Argument & argument, const SerializationFormat& format);
      bool serializeToFile(const std::string & filename, const Argument & argument);
      bool serializeToFile(const std::string & filename, const Argument & argument, const SerializationFormat & format);
      // returns true if a deserializer exists for the specified format
      bool deserializerExists(const SerializationFormat & format);
      // returns a serializer for the specified format 
      DeserializerType deserializerFor(const SerializationFormat & format);
      // returns a list of all deserializers
      const std::vector<DeserializerType> & deserializers();
      // deserializes an argument impling the type from the input data using the serialization format
      Argument deserialize(std::istream & stream,const SerializationFormat & format);
      // deserializes a object of type from the stream whose format is "format"
      Argument deserialize(std::istream & stream, const Type * type, const SerializationFormat & format);
      // deserializes the string passed as first argument into an instance of type using the format
      Argument deserialize(const std::string & serialized, const Type * type, const SerializationFormat & format);
      // deserializes a file and uses the filename / or content to imply the type
      Argument deserializeFromFile(const SerializationFormat & filename);
      //deserializes a file into an Argument of type "type" and implies the serialized format
      Argument deserializeFromFile(const std::string & filename, const Type * type);
      //deserializes a file into an Argument of type "type" and format format
      Argument deserializeFromFile(const std::string & filename, const Type * type, const SerializationFormat & format);
      // deserializes a T from the strim using the specified format
      template<typename T> T deserialize(std::istream & stream, const SerializationFormat & format);      
      template<typename T> bool deserialize(std::shared_ptr<T> outPtr, std::istream & stream, const SerializationFormat & format);
    }
  }
}
///template implementation


namespace nspace{
  namespace core{
    namespace serialization{
      // deserializes a T from the strim using the specified format
      template<typename T> T deserialize(std::istream & stream, const SerializationFormat & format){
        auto type = type_of<T>();
        Argument result = deserialize(stream,type,format);
        if(result.isValid())throw new std::exception("could not correctly deserialize object ");
        return result;
      }
      template<typename T> bool deserialize(std::shared_ptr<T> outPtr, std::istream & stream, const SerializationFormat & format){        
        auto type = type_of<T>();
        Argument result = deserialize(stream,type,format);
        if(result.isValid())return false;
        outPtr = result.cast<T>();
        return true;
      }
    }
  }
}
/*
#include <string>
#include <config.h>
#include <core.collection/containers/Set.h>
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

// pointer serializers
template<typename T>
class Deserializer<T*>{
public:
static bool deserialize(T ** result, std::istream & in){
return false;
}
};
template<typename T>
class Serializer<T*>{
public:
static bool serialize(std::ostream & out, const T ** in){
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

template<typename T>
bool deserialize(T & value, std::istream & stream){
return Deserializer<T>::deserialize(&value,stream);  
}
template<typename T>
T deserialize(std::istream & stream){
T value;
deserialize(value,stream);
return value;
}
template<typename T>
bool serialize(const T & value, std::ostream & stream){
return Serializer<T>::serialize(stream,&value);
}


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
for(uint i=0; i< val; i++){
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
}*/
