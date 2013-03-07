#pragma once
#include <core/patterns/Singleton.h>

#include <scripting.python/PythonUtilities.h>

namespace nspace{


struct PythonMethodType:  PyTypeObject{
  SINGLETON(PythonMethodType);


};

}