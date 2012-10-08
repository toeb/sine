#pragma once
#include <config.h>

//defines a the class as a singleton
#define SINGLETON(CLASSNAME)\
  public: \
  static CLASSNAME * instance(){\
  static CLASSNAME * _instance =0;\
  if(!_instance)_instance = new CLASSNAME();\
  return _instance;\
}\
private:\
  CLASSNAME()
/*  Example of a class using the singleton macro

class TestClass{
 SINGLETON(TestClass){
   // constructor code here
 }
};

*/


