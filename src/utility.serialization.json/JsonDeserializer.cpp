#include "JsonDeserializer.h"
#include <json/json.h>

using namespace nspace;
using namespace nspace::core;
using namespace nspace::core::serialization;

using namespace std;
using namespace Json;


const Type * mapTypeFromJson(ValueType jtype){
  string typeName;
  switch(jtype){
  case ValueType::arrayValue:
    break;
  case ValueType::booleanValue:
    return typeof(bool);
    break;
  case ValueType::intValue:
    return typeof(int);
    break;
  case ValueType::nullValue:
    break;
  case ValueType::objectValue:
    break;
  case ValueType::realValue:
    return typeof(double);
    break;
  case ValueType::stringValue:    
    return typeof(std::string);
    break;
  case ValueType::uintValue:
    return typeof(unsigned int);
    break;
  default:
    break;
  }
  if(typeName=="")return 0;
  
  auto result = NamespaceInfo::Global()->findChild(typeName);
  auto type = dynamic_cast<const Type*>(result);
  return type;
}

template<typename T>
Argument mapValue(T value){
  auto type = typeof(T);
  Argument result = value;
}

Argument mapValueFromJson(Json::Value value){  
  switch(value.type()){
    case ValueType::arrayValue:
    break;
  case ValueType::booleanValue:
    return value.asBool();
    break;
  case ValueType::intValue:
    return value.asInt();
    break;
  case ValueType::nullValue:
    break;
  case ValueType::objectValue:
    break;
  case ValueType::realValue:
    return value.asDouble();
    break;
  case ValueType::stringValue: 
    return value.asString();
    break;
  case ValueType::uintValue:
    return value.asUInt();
    break;
  default:
    break;
  }
  return Argument();


}

ValueType mapTypeToJson(const Type* type){
  return ValueType::nullValue;
}

Argument JsonDeserializer::doDeserialization(std::istream & stream){

  Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(stream,root,true);
  if(!parsingSuccessful){
    logWarning("Failed to parse json input data");
    return Argument();
  }

  auto result = mapValueFromJson(root);  

  return result;
};