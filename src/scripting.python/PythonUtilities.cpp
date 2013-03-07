#include "PythonUtilities.h"

#include <scripting.python/PythonObject.h>
#include <scripting.python/PythonType.h>
#include <scripting.python/PythonScriptMachine.h>
using namespace nspace;


Argument nspace::pythonObjectToArgument(PyObject * object, const Type * type){
    if(type==typeof(int)){
    if(!PyNumber_Check(object))return Argument();
    auto l = PyNumber_Long(object);
    
    auto ll = (int)PyLong_AsLong(l);
    return ll;
  }

  return Argument();
}