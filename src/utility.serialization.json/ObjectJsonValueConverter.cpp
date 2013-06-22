#include "ObjectJsonValueConverter.h"
#include <json/json.h>
#include <core.logging.h>
using namespace nspace::core::serialization;
using namespace nspace;
using namespace Json;


bool ObjectJsonValueConverter::canConvert(const Argument & value)const {
  return true;
} 
Json::Value ObjectJsonValueConverter::convert(const Argument & argument,SerializationContext & context)const{
  Value result;
  auto id = context.getId(argument.data);
  // if id extists this object was already processed an thus only a reference is returned (object with only an $_id field)
  if(id){    
    result["$_id"] =  id;
    return result;
  }

  auto type = argument.type;
  auto typeName = type->getFullyQualifiedName();

  if(type->getIsPointer()){
    logWarning("currently raw pointers are not serializeable");
    return Value::null;
  }

  // create id
  id = context.requireId(argument.data);
  // assign it to special fields $_id and also assign type name
  result["$_id"] =  id;
  result["$_t"] = typeName;

  // handle pointer to primitives/custom serialized properties
  auto converter = JsonValueConverter::Get(argument);
  if(converter!=this){
    result["$_value"]=converter->convert(argument,context);
    return result;
  }

  // handle properties of object
  type->Properties().foreachElement([&](const PropertyInfo * info ){
    auto name = info->getName();
    auto propertyType = info->getPropertyType();
    auto arg = info->get(argument.data.get());      

    // since shared pointers are treated specially in the reflection object model
    // they are handled here
    if(propertyType->getTemplateName()=="shared_ptr"){
      if(!arg.isValid()){
        // arg is only invalid if pointer is null
        result[name] = Value::null;
      }else{
        // if current is a shared_ptr directly convert instead of search for a converter
        result[name] = convert(arg,context);
      }

    }

    // this should not happen since only shared_ptr is treaded specially
    if(arg.type!=info->getPropertyType())return;

    // get a converter for the current property
    auto converter = JsonValueConverter::Get(arg);
    if(!converter)return;
    result[info->getName()] = converter->convert(arg,context);
  });


  return result;
}
