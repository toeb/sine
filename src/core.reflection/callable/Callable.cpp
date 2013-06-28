#include "Callable.h"
#include <core.reflection/type/TypeInfo.h>
#include <core.reflection.builder.h>
using namespace nspace;



const Type* Callable::getType()const{
  return type_of<Callable>();
}
bool Callable::initializeType(){
  core::reflection::builder::reflect<Callable>()
    ->fullyQualifiedName(DS_STRINGIFY(nspace::Callable))
    ->publishHierarchy()
    ->end();
  return true;
}

//reflect_type_default_definition(nspace::Callable);
/*
const Type * Callable::getType()const{
return ds::type_of<CurrentClassType>();
}
void ds::Callable::_reflectType(){
ds::core::reflection::builder::reflect<CurrentClassType>() 
->fullyQualifiedName((std::function<std::string ()>([&]()->std::string {std::ostringstream stream; stream << "::"<<"nspace::Callable"; return stream.str(); }) () )) 
->publishHierarchy() 
->end(); 
};
*/

Argument Callable::operator()(){
  return callImplementation(std::vector<Argument>());
}

Argument Callable::operator()()const{
  return callImplementation(std::vector<Argument>());
}


Argument Callable::call(){
  return callImplementation(std::vector<Argument>());
}

Argument Callable::call()const{
  return callImplementation(std::vector<Argument>());
}


Argument Callable::callImplementation(const Arguments & args){return ((const Callable*)this)->callImplementation(args);};
Argument Callable::callImplementation(const Arguments & args)const{return Argument();}