#pragma once
#include <config.h>
#include <core/template/TemplateUtilities.h>

#include <memory>
namespace nspace{


#define DS_SINGLETON_TYPE(CLASSNAME,TEMPLATEARGUMENTS) typedef CLASSNAME TEMPLATEARGUMENTS SingletonType;
  // todo remove if !_instance 
#define DS_SINGLETON_IMPL(CLASSNAME)                                              \
  static std::shared_ptr<SingletonType> instance(){                               \
  static std::shared_ptr<SingletonType> _instance;                                \
  if(!_instance)_instance = std::shared_ptr<SingletonType>(new SingletonType());  \
    return _instance;                                                             \
  }                                                                               \
  private:                                                                        \
  CLASSNAME()

#define DS_SINGLETON_TEMPLATED(CLASSNAME,TEMPLATEARGUMENTS)\
  public:\
  DS_SINGLETON_TYPE(CLASSNAME,TEMPLATEARGUMENTS);\
  DS_SINGLETON_IMPL(CLASSNAME)

#define DS_SINGLETON(CLASSNAME) DS_SINGLETON_TEMPLATED(CLASSNAME,)

#define TEMPLATEDSINGLETON(CLASSNAME,TEMPLATEARGUMENTS) DS_SINGLETON_TEMPLATED(CLASSNAME,TEMPLATEARGUMENTS)

//defines a the class as a singleton (private constructor and public static instance() method returning a shared ptr
#define SINGLETON(CLASSNAME) DS_SINGLETON(CLASSNAME)





/*  Example of a class using the singleton macro

class TestClass{
SINGLETON(TestClass){
// constructor code here
}
};

*/

}