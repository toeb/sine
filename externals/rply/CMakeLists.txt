set(source rply.h rply.cpp)
source_group("" FILES ${source})
add_library(rply ${source} CMakeLists.txt)
project_folder("externals" rply)
