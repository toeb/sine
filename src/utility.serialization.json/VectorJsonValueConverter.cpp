#include "VectorJsonValueConverter.h"

using namespace nspace::core::serialization;
using namespace nspace;
bool VectorJsonValueConverter::canConvert(const Argument & argument)const  {
  auto name = argument.type->getFullyQualifiedTemplateName();
  if(name=="::std::vector"){
    return true;
  }
  return false;
}
Json::Value VectorJsonValueConverter::convert(const Argument & value, SerializationContext & context)const  {
  Json::Value result(Json::arrayValue);

  auto size=MethodAdapter(value,"size");
  auto at = MethodAdapter(value,"at");

  // get converter for first element 
  // return empty result if size is 0 or no converter can be found
  size_t n= size();
  if(n==0)return result;
  auto converter  = JsonValueConverter::Get(at(0));
  if(!converter)return result;

  // loop trhough erlements and convert each
  for(size_t i=0; i < n; i++){
    auto item = at(i);
    auto jvalue = converter->convert(item,context);
    result[i] = jvalue;
  }

  return result;
}


