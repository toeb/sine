set(source 
 Javascript.h
 Javascript.cpp
 ../include/scripting.javascript.h
)

add_library(scripting.javascript ${source} CMakeLists.txt)
target_link_libraries(scripting.javascript scripting)