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


  

  IntValue::IntValue(const string & name, function<int ()> get,function<void (int v)> set):IValue(name){
    setter = set;
    getter = get;
  }
  void IntValue::set(const void * val){
    const int * realValue = reinterpret_cast<const int*>(val);
    setter(*realValue);
  }
  void IntValue::get(void * val){
    int * value = reinterpret_cast<int*>(val);
    *value = getter();
  }