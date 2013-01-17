set(source 
PlyReader.h
PlyReader.cpp
 ../include/utility.reader.ply.h
)


source_group("" FILES ${source})
add_library(utility.reader.ply ${source} CMakeLists.txt)
target_link_libraries(utility.reader.ply utility.reader simulation.geometry rply)