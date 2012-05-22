#include "RealValue.h"

using namespace std;
using namespace IBDS;



  RealValue::RealValue(const string & name, function<Real ()> get,function<void (Real v)> set):IValue(name){
    setter = set;
    getter = get;
  }
  void RealValue::set(const void * val){
    const Real * realValue = reinterpret_cast<const Real*>(val);
    setter(*realValue);
  }
  void RealValue::get(void * val){
    Real * value = reinterpret_cast<Real*>(val);
    *value = getter();
  }