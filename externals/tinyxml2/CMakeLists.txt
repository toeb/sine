set(source tinyxml2.h tinyxml2.cpp)
source_group("" FILES ${source})
add_library(tinyxml2 ${source} CMakeLists.txt)
project_folder("externals" tinyxml2)
