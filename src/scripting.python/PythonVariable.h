#pragma once
#include <Python.h>
#include <core.reflection.h>
namespace nspace{
  
struct PythonVariable{
  PythonVariable(const std::string  &name);


  PythonVariable  & operator = (Argument argument);

  bool assign(Argument argument);
  operator Argument();
  Argument toArgument(const Type * type=0);


  std::string module;
  std::string name;
};
}