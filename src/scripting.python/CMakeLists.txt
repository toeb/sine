set(source 
 PythonType.h
 PythonType.cpp
 PythonObject.h
 PythonObject.cpp
 PythonScriptMachine.h
 PythonScriptMachine.cpp
 PythonMethodAdapter.h
 PythonUtilities.h
 PythonUtilities.cpp
 PythonVariable.h
 PythonVariable.cpp
 PythonFunction.h
 PythonFunction.cpp
 PythonDynamicObjectImplementation.h
 PythonDynamicObjectImplementation.cpp
 PythonMethodAdapter.cpp
 ../include/scripting.python.h

)

find_package(PythonLibs 3)
find_package(PythonInterp 3)

if(PYTHONLIBS_FOUND)
include_directories(${PYTHON_INCLUDE_DIRS})
add_library(scripting.python ${source} CMakeLists.txt)
target_link_libraries(scripting.python scripting ${PYTHON_LIBRARIES} )

else(PYTHONLIBS_FOUND)
message("  could not find python libs - scripting.python and its dependents will not be included")
endif(PYTHONLIBS_FOUND)