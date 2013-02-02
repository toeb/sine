#pragma once
#include <config.h>
#include <core/template/TemplateUtilities.h>


namespace nspace{

#define TEMPLATEDSINGLETON(CLASSNAME, TEMPLATEARGUMENTS)\
  public:\
  typedef CLASSNAME TEMPLATEARGUMENTS SingletonType;\
  static SingletonType * instance(){\
  static SingletonType * _instance;\
  if(!_instance)_instance = new SingletonType();\
  return _instance;\
  }\
  private:\
  CLASSNAME()

//defines a the class as a singleton
#define SINGLETON(CLASSNAME)\
  public: \
  typedef CLASSNAME SingletonType;\
  static SingletonType * instance(){\
  static SingletonType * _instance =0;\
  if(!_instance)_instance = new SingletonType();\
  return _instance;\
}\
private:\
  CLASSNAME()


  // compile time check if type is singleton.
template <typename T>
struct is_singleton{
private:
    template <typename T1>
    static typename T1::SingletonType test(int);
    template <typename>
    static void test(...);
public:
    enum { value = !std::is_void<decltype(test<T>(0))>::value };
};


/*  Example of a class using the singleton macro

class TestClass{
SINGLETON(TestClass){
// constructor code here
}
};

*/

}