set(source 
 Scripting.h
 Scripting.cpp
 ../include/scripting.h
)

add_library(scripting ${source} CMakeLists.txt)
target_link_libraries(scripting core)