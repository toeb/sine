#pragma once

#include <utility/valuegraph/TypedValue.h>

namespace nspace{
template<typename T>
class CachedValue : public TypedValue<T>{
private:
  VersionId _cachedVersion;
  TypedValue<T> & _value;
public:
  CachedValue(TypedValue<T> & value):_value(value){

  }
  void cache(){
    _cachedVersion = _value.version();
    set(_value.get());
  }
  bool dirty()const{
    return _cachedVersion!=_value.version();
  }
};

}