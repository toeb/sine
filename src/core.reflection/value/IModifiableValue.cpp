#include "IModifiableValue.h"
using namespace nspace;

bool IModifiableValue::changeValue(Argument value){
  bool cancel = false;
  valueChanging(value,cancel);
  if(cancel)return false;
  bool success = storeValue(value);
  if(success) raiseObjectChanged();
  return success;
}



IModifiableValue::IModifiableValue(){}
IModifiableValue::IModifiableValue(const Type * valueType):IReadableValue(valueType){}

bool IModifiableValue::set(Argument argument){
  return changeValue(argument);
}