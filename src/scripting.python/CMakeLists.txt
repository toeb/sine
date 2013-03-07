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
 PythonMethodAdapter.cpp
 ../include/scripting.python.h

)

add_library(scripting.python ${source} CMakeLists.txt)


find_package(PythonLibs 3)
find_package(PythonInterp 3)

include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(scripting.python scripting ${PYTHON_LIBRARIES} )