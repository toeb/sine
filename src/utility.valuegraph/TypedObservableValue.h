#pragma once

#include <utility.valuegraph/TypedValue.h>
#include <utility.valuegraph/ObservableValue.h>
namespace nspace{

template<typename T>
class TypedObservableValue : public virtual TypedValue<T>, public virtual ObservableValue{
public:
  TypedObservableValue(const T & init):TypedValue(init){}
TypedObservableValue():TypedValue(){}

};
}