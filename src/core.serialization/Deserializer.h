#pragma once

#include <core.reflection.h>


#include <core.reflection/dynamic/DynamicObject.h>
#include <istream>
namespace nspace{
namespace core{
namespace serialization{
class Deserializer{
protected:
  virtual bool deserialize(DynamicObject object, std::istream & stream);
};
}
}
}