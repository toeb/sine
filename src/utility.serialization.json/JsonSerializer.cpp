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
    return getId(ptr);
  }
  int getId(Argument & argument){
  auto type = argument.type;
    type->getIsPointer()
  }
};


class CustomSerializer{
public:
  virtual bool canSerialize(const Type * type)=0;
  virtual bool serialize(std::ostream & stream,  Argument argument)=0;
};

template<typename T>
class TypedCustomSerializer : public CustomSerializer{
  virtual bool canSerialize(const Type* type)override{
    return type_of<T>()==type;
  }

  virtual bool serialize(std::ostream & stream,  Argument argument){
    typedSerializer(stream,argument);
  }

  bool typedSerializer(std::ostream & stream,  const T & argument){
    return false;
  }
};

// simplify creating serilaizer
#define DS_CUSTOM_TYPED_SERIALIZER_FOR(TYPE) template<> bool TypedCustomSerializer<TYPE>::typedSerializer(std::ostream & stream,  const TYPE & value)

DS_CUSTOM_TYPED_SERIALIZER_FOR(int){

}

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
  virtual Json::Value convert(const Argument & argument)const=0;
};
template<typename T>
struct TypedJsonValueConverter : public JsonValueConverter{
  virtual bool canConvert(const Argument & argument)const override {return type_of<T>()==argument.type;}
  virtual Json::Value convert(const Argument & value)const override {
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


template<typename TContainer>
struct SizeType{
  typedef void type;
};

template<typename TElement>
struct SizeType<std::vector<TElement>>{
  typedef typename std::vector<TElement>::size_type type;
};

template<typename TContainer>
struct ElementType{
  typedef void* type;
};
template<typename TElement>
struct ElementType<std::vector<TElement>>{
  typedef TElement type;
};

// for references
template<typename TContainer>
struct ElementType<TContainer&>{
  typedef typename ElementType<typename TContainer>::type type;
};
//for pointers
template<typename TContainer>
struct ElementType<TContainer*>{
  typedef typename ElementType<typename TContainer>::type type;
};

template<typename TContainer>
struct ElementType<const TContainer>{
  typedef typename ElementType<typename TContainer>::type type;
};

template<typename TContainer>
struct ElementCount{
  static inline auto count(const TContainer & container)->size_t{
    throw new exception("count is not implemented for type");
  }
};

template<typename TElement>
struct ElementCount<std::vector<TElement>>{
  static inline auto count(const std::vector<TElement> & container)->size_t{
    return container.size();
    
  }
};


template<typename TContainer>
size_t count(const TContainer & container){
  ElementCount<TContainer>::count(container);
}

template<typename TContainer>
struct ElementAt{
  typedef typename ElementType<TContainer>::type TElement;
public:
  static inline TElement & elementAt(TContainer & container, size_t i){
    throw new exception("elementAt is not implement for type");
  }
};

template<typename TContainer>
struct ElementAtConst{
  typedef typename ElementType<TContainer>::type TElement;
public:
  static inline const TElement & elementAt(const TContainer & container, size_t i){
    throw new exception("elementAt (const) is not implement for type");
  }
};

template<typename TElement>
struct ElementAt<std::vector<TElement>>{
public:
  static inline TElement & elementAt(std::vector<TElement> & container, size_t i){
    return container.at(i);
  }
};

template<typename TContainer>
struct Predicate{
  typedef typename std::function<bool (typename const ElementType<TContainer>::type & )> type;
};



template<typename TContainer>
struct OperationFirstOrDefault{
  static inline auto firstOrDefault(TContainer & container, typename Predicate<TContainer>::type predicate)->typename ElementType<TContainer>::type{
    throw new exception("firstOrDefault not implemented for type");
  }
};



template<typename TElement>
struct OperationFirstOrDefault<std::vector<TElement>>{
  static inline auto firstOrDefault(std::vector<TElement> & container,typename Predicate<std::vector<TElement>>::type predicate)->typename TElement &{
     for(int i=0; i < container.size(); i++){
       if(predicate(container[i]))return container[i];
     }
     return 0;
  }
};


template<typename TContainer>
auto firstOrDefault(TContainer & container, typename Predicate<TContainer>::type predicate)->typename ElementType<TContainer>::type{
  return OperationFirstOrDefault<TContainer>::firstOrDefault(container,predicate);
}

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

std::string JsonSerializer::serialize(Argument value){
  //auto t = ElementType<decltype(JsonValueConverter::Converters())>::type();
  /*auto converter = firstOrDefault(JsonValueConverter::Converters(), [&value](const JsonValueConverter * converter){
    return converter->canConvert(value.type);
  });*/
  const JsonValueConverter * converter = getConverter(value);
  Value root;
  if(converter){
    root = converter->convert(value);    
  }else{    
    int objectId=1;
    map<std::shared_ptr<void>,int> ids;

    auto ptr = value.cast<void>();
    int id;
    if(ids.find(ptr)==std::end(ids)){
      id = objectId++;
      ids[ptr]=id;
    }else{
      id= ids[ptr];
    }

    string typeName = value.type->getFullyQualifiedName();
    root["$_t"] = typeName;
    root["$_id"] =  id;


    value.type->Properties().foreachElement([&](const PropertyInfo * info ){
      auto name = info->getName();
      auto arg = info->get(value.data.get());
      if(arg.type!=info->getPropertyType())return;
      auto converter = getConverter(info->get(value.data.get()));
      if(!converter)return;
      root[info->getName()] = converter->convert(arg);
    });


  }


  stringstream stream;
  stream << root;
  auto str = stream.str();
  return str;

}

JsonSerializer::JsonSerializer(){

}
