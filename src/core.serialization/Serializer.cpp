#include "Serializer.h"
#include <string>
using namespace nspace;
using namespace nspace::core::serialization;

Serializer::Serializer(const SerializationFormat & format):_Format(format){
}
std::string Serializer::serialize(const Argument & value)const{
  std::stringstream stream;
  auto result = serialize(stream,value);
  return stream.str();
}
bool Serializer::serialize(std::ostream & stream, const Argument & value)const{
  SerializationContext context;
  return doSerialization(stream,value,context);
}
