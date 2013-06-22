#include "JsonSerializer.h"

#include <json/json.h>
#include <utility.serialization.json/JsonValueConverter.h>
#include <utility.serialization.json/TypedJsonValueConverter.h>

#include <utility.serialization.json/VectorJsonValueConverter.h>
#include <utility.serialization.json/ObjectJsonValueConverter.h>


using namespace nspace;
using namespace nspace::core;
using namespace nspace::core::serialization;

using namespace Json;
using namespace std;

// instanciate converters (order matters)

TypedJsonValueConverter<int> intConverter;
TypedJsonValueConverter<std::string> stringConverter;
TypedJsonValueConverter<double> doubleConverter;
TypedJsonValueConverter<float> floatConverter;
TypedJsonValueConverter<unsigned int> uintConverter;
TypedJsonValueConverter<bool> boolConverter;
VectorJsonValueConverter vectorConverter;
ObjectJsonValueConverter objectConverter;




bool JsonSerializer::doSerialization(std::ostream & stream, const Argument & value){
  // get a converter for value
  const JsonValueConverter * converter = JsonValueConverter::Get(value);  
  if(!converter)return false;
  // instanciate a context 
  SerializationContext context;
  // actually convert the value and then return the string
  Value root = converter->convert(value,context);
  stream << root;
}

JsonSerializer::JsonSerializer(){

}
