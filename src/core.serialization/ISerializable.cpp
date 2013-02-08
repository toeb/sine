#include "ISerializable.h"
#include <core.reflection/type/TypeInfo.h>
using namespace nspace;



bool ISerializeable::toStream(std::ostream & stream, Format format){return false;}
bool  ISerializeable::fromStream(std::istream & stream, Format format){return false;}
void  ISerializeable::onSerialized(){}
void ISerializeable:: onDeserialized(){}
bool  ISerializeable::serialize(std::ostream & stream, Format format){
  bool success = toStream(stream,format);
  if(success)onSerialized();
  return success;
}
bool  ISerializeable::deserialize(std::istream & stream, Format format){
  bool success = fromStream(stream,format);
  if(success)onDeserialized();
  return success;
}