#include "DelegateValue.h"

using namespace std;
using namespace IBDS;

template<class T>
DelegateValue<T>::DelegateValue(const std::string & name, std::function<T()> getter, std::function<void (T)> setter):IValue(name), _setter(setter), _getter(getter){};

template<class T>
void DelegateValue<T>::set(const void * value){
  const T * typedValue = reinterpret_cast<const T*>(value);
  _setter(*typedValue);
}

template<class T>
void DelegateValue<T>::get(void * value){
  T * typedValue = reinterpret_cast<T*>(value);
  *typedValue = _getter();
}

