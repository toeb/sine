#include "IReadableValue.h"
#include <core.reflection/type/TypeInfo.h>
#include <core.reflection.builder.h>
using namespace nspace;

reflect_type_default_definition(nspace::IReadableValue);



IReadableValue::IReadableValue():_ValueType(0){}


IReadableValue::IReadableValue(const Type * valueType):_ValueType(valueType){}

Argument IReadableValue::get()const {
  return retrieveValue();
}

