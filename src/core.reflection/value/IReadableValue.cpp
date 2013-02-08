#include "IReadableValue.h"
#include <core.reflection/type/TypeInfo.h>
using namespace nspace;

DS_CLASS_DEFINITION(IReadableValue);


bool IReadableValue::getByPointer(void * result)const{
  return retrieveValue(result);
}
IReadableValue::IReadableValue():_ValueType(0){}