#include "IReadableValue.h"
#include <core.reflection/type/TypeInfo.h>
using namespace nspace;





IReadableValue::IReadableValue():_ValueType(0){}


IReadableValue::IReadableValue(const Type * valueType):_ValueType(valueType){}

Argument IReadableValue::get()const {
  return retrieveValue();
}

