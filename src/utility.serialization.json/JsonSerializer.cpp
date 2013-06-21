#include "JsonSerializer.h"

#include <json/json.h>

using namespace nspace;
using namespace nspace::core;
using namespace nspace::core::serialization;

using namespace Json;
using namespace std;

template<typename TTarget,typename TSource>
class CustomConverter{
public:
  bool canConvert(){return false;}
  TTarget convert(TSource source){return source;}
};



class SerializationContext{
  int idCounter;
  std::map<void*, int> pointerIds;
public:
  SerializationContext():idCounter(1){
  }
  int getId(void* ptr){
    auto it = pointerIds.find(ptr);
    if(it==std::end(pointerIds)){
      int id = idCounter++;
      pointerIds[ptr] = id;      
    }
    return pointerIds[ptr];
  }
  int getId(std::shared_ptr<void> ptr){
    return getId(ptr.get());
  }
  int getId(Argument & argument){
    auto type = argument.type;    
    return 0;
  }
};


struct JsonValueConverter;
std::vector<const JsonValueConverter*> converters;

struct JsonValueConverter{
  static const std::vector<const JsonValueConverter*> & Converters(){
    return converters;
  }
  JsonValueConverter(){
    converters.push_back(this);
  }
  virtual bool canConvert(const Argument & argument)const=0;
  virtual Json::Value convert(const Argument & argument,SerializationContext & context)const=0;
};
template<typename T>
struct TypedJsonValueConverter : public JsonValueConverter{
  virtual bool canConvert(const Argument & argument)const override {return type_of<T>()==argument.type;}
  virtual Json::Value convert(const Argument & value, SerializationContext & context)const override {
    Json::Value result;
    typedConvert(result,value);
    return result;
  }
  void typedConvert(Json::Value & result, const T & value)const{return false;}
};
// specialization
#define DS_TYPED_JSON_VALUE_CONVERTER_FOR(TYPE)\
  template<> void TypedJsonValueConverter<TYPE>::typedConvert(Json::Value & result, const TYPE & value)const

//shorthand
#define JVC(TYPE) DS_TYPED_JSON_VALUE_CONVERTER_FOR(TYPE)

#define JVCI(TYPE) TypedJsonValueConverter<TYPE> DS_CONCAT(__ConverterInstance,__LINE__)
JVC(int){
  result = value;
}
JVCI(int);
JVC(double){
  result = value;
}
JVCI(double);
JVC(float){
  result = (double)value;
}
JVCI(float);
JVC(std::string){
  result = value;
}
JVCI(std::string);
JVC(unsigned int){
  result = value;
}
JVCI(unsigned int);

const JsonValueConverter *  getConverter(const Argument & value){
  const JsonValueConverter * converter = 0;
  for(auto it : JsonValueConverter::Converters()){
    if(it->canConvert(value)){
      converter = it;
      break;
    }
  }
  return converter;
}

struct JsonObjectConverter : JsonValueConverter{
  bool canConvert(const Argument & value)const override{
    return true;
  } 
  virtual Json::Value convert(const Argument & argument,SerializationContext & context)const{
    Value result;
    auto type = argument.type;
    auto typeName = type->getFullyQualifiedName();

    auto id = context.getId(argument.data);


    result["$_t"] = typeName;
    result["$_id"] =  id;


    argument.type->Properties().foreachElement([&](const PropertyInfo * info ){
      auto name = info->getName();
      auto arg = info->get(argument.data.get());
      if(arg.type!=info->getPropertyType())return;
      auto converter = getConverter(info->get(argument.data.get()));
      if(!converter)return;
      result[info->getName()] = converter->convert(arg,context);
    });
    return result;
  }
}__instance;

std::string JsonSerializer::serialize(Argument value){

  const JsonValueConverter * converter = getConverter(value);
  Value root;
  if(!converter)return "";
  SerializationContext context;
  root = converter->convert(value,context);

  stringstream stream;
  stream << root;
  auto str = stream.str();
  return str;

}

JsonSerializer::JsonSerializer(){

}
