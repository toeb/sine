set(source 
 Ruby.h
 Ruby.cpp
 ../include/scripting.ruby.h
)

add_library(scripting.ruby ${source} CMakeLists.txt)
target_link_libraries(scripting.ruby scripting )