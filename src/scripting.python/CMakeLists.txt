set(source 
 Python.h
 Python.cpp
 ../include/scripting.python.h
)

add_library(scripting.python ${source} CMakeLists.txt)


find_package(PythonInterp)
find_package(PythonLibs)

include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(scripting.python scripting ${PYTHON_LIBRARIES} )