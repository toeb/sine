set(source 
 Python.h
 Python.cpp
 ../include/scripting.python.h
)

add_library(scripting.python ${source} CMakeLists.txt)
target_link_libraries(scripting.python scripting)