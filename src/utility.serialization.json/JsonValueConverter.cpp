#include "JsonValueConverter.h"

using namespace nspace::core::serialization;
using namespace nspace;


std::shared_ptr<std::vector<const JsonValueConverter*>> converters;

const JsonValueConverter * JsonValueConverter::Get(const Argument & value){
  const JsonValueConverter * converter = 0;
  for(auto it : JsonValueConverter::Converters()){
    if(it->canConvert(value)){
      converter = it;
      break;
    }
  }
  return converter;
}
std::vector<const JsonValueConverter*> & JsonValueConverter::Converters(){
  static std::vector<const JsonValueConverter*> converters;
  return converters;
}
JsonValueConverter::JsonValueConverter(){ 
  Converters().push_back(this);
}

