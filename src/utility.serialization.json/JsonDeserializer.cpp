#include "JsonDeserializer.h"
#include <json/json.h>
#include <core.logging.h>
#include <core.reflection/dynamic/DynamicObject.h>
using namespace nspace;
using namespace nspace::core;
using namespace nspace::core::serialization;

using namespace std;
using namespace Json;

JsonDeserializer::JsonDeserializer():Deserializer("json"){

}

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

Argument convert(Value & root, const Type* type,DeserializationContext  &context){
  auto result = mapValueFromJson(root);  
  if(result.isValid())return result;

  auto id = root["$_id"].asInt();  
  if(id){
    result = context.getPointer(id);

  }
  // somewhere i have to add $_value handling

  // if no instance was created yet for id get the type and create it
  if(!result.isValid()){
    auto typeName = root["$_t"].asString(); 
    auto impliedType = static_cast<const Type*>(Type::Global()->findScope(typeName));
    if(!type)type = impliedType;  
    if(type) {
      result = type->call();
      // if id is set register the pointer at id
      if(id){
        result = context.requirePointer(id,result);
      }
    }else{
      // if type is not valid a dynamic object is created
      throw new std::exception("not implemented yet");
    }
  }
  // if no result is set until now return an error result
  if(!result.isValid())return Argument();

  // $_value field exists the value is either a primitve pointer or a custom serialized field
  if(!root["$_value"].empty()){
    auto valueJ = root["$_value"];
    auto valueArg =mapValueFromJson(valueJ);
    if(!valueArg.isValid()){
      return Argument();// maybe error?
    }
    // set id to point to this value
    context.requirePointer(id,result);
    return valueArg;
  }


  // if type is set (no dynamic object)
  if(type){
    for(int i=0;i < type->Properties().size(); i++){
      auto property = type->Properties().at(i);
      auto propertyType = property->getPropertyType();
      auto name = property->getName();
      Value jvalue = root[name];
      if(jvalue.empty()){
        continue;
      }
      auto value  = convert(jvalue,propertyType,context);
      property->set(result.data.get(),value);
    }
  }else{
    // will not happen because an exception is thrown earlier (dynamic object deserialization is not yet implemented)
  }



  return result;
}
Argument JsonDeserializer::doDeserialization(std::istream & stream,const Type* type, DeserializationContext & context)const{

  Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(stream,root,true);
  if(!parsingSuccessful){
    logWarning("Failed to parse json input data");
    return Argument();
  }

  return convert(root,type,context);
};