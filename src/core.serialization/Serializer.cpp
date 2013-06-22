#include "Serializer.h"
#include <string>
using namespace nspace;
using namespace nspace::core::serialization;

std::string Serializer::serialize(const Argument & value){
  std::stringstream stream;
  auto result = serialize(stream,value);
  return stream.str();
}
bool Serializer::serialize(std::ostream & stream, const Argument & value){
  return doSerialization(stream,value);
}
