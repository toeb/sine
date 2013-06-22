#include "Deserializer.h"


using namespace nspace;
using namespace nspace::core;
using namespace nspace::core::serialization;

using namespace std;
Deserializer::Deserializer(const SerializationFormat & format):_Format(format){
}
Argument Deserializer::deserialize(const std::string & str)const{
  stringstream stream(str);
  return deserialize(stream);
}
Argument Deserializer::deserialize(const std::string & str, const Type* type)const{
  stringstream stream(str);
  return deserialize(stream);
}

Argument Deserializer::deserialize(std::istream & stream)const{
  return deserialize(stream,0);
}

Argument Deserializer::deserialize(std::istream & stream,const Type* type)const{
  DeserializationContext context;
  return doDeserialization(stream,type,context);
}

Argument Deserializer::deserializeFile(const std::string & filename)const{
  return deserializeFile(filename, 0);
}
Argument Deserializer::deserializeFile(const std::string & filename, const Type* type)const{

  ifstream stream(filename);
  if(!(bool)stream)return Argument();
  return deserialize(stream,type);
}

