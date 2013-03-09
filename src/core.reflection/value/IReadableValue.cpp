#include "IReadableValue.h"
#include <core.reflection/type/TypeInfo.h>
using namespace nspace;





IReadableValue::IReadableValue():_ValueType(0){}


Argument IReadableValue::get()const {
  return retrieveValue();
}