#include "Deserializer.h"


using namespace nspace;
using namespace nspace::core;
using namespace nspace::core::serialization;


Argument Deserializer::deserialize(const std::string & str){
  readString(str);
  return getDeserializationResult();
}
Argument Deserializer::deserialize(std::istream & stream){  
  readStream(stream);
  return getDeserializationResult();
}
Argument Deserializer::deserializeFile(const std::string & filename){  
  readFile(filename);
  return getDeserializationResult();
}
bool Deserializer::doRead(){
  // reset result to invalid argument
  setDeserializationResult(Argument());
  auto result =  doDeserialization(stream());
  setDeserializationResult(result);
  return result.isValid();
}