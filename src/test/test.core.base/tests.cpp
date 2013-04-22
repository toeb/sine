/**
 * \file  src\test\core.base\tests.cpp
 *
 * \brief Contains basic tests that are written in pure c++ (because testing framework uses core).
 */
#include <core/Object.h>
#include <core/PropertyChangingObject.h>


#include <core.reflection.h>


bool objectInstanciation(){
  // test just checks object instanciation (this is rather a compile test)
 using namespace nspace;
  Object o;
  return true;
}

bool objectType(){
  // checks wether the correct typename is returned
  using namespace nspace;
  Object o;

  auto type = o.getType();
  if(!type)return false;
  
  auto name = type->getName();
  if(name!="Object")return false;

  return true;
}




int main(){
  if(!objectInstanciation())return -1;
  if(!objectType())return -1;

  return 0;
}