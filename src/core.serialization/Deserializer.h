#pragma once

#include <core.reflection.h>
#include <utility.reader/Reader.h>
#include <istream>
namespace nspace{
namespace core{
namespace serialization{
class Deserializer : public Reader{
  reflect_type(Deserializer);
  reflect_superclasses(Reader);

  typedef Argument reflect_property(DeserializationResult);

protected:
  virtual Argument doDeserialization(std::istream & stream)=0;
  bool doRead()override;
public:
  Argument deserialize(const std::string & str);
  Argument deserialize(std::istream & stream);
  Argument deserializeFile(const std::string & filename);
};
}
}
}