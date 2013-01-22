set(source 
 ./ObjReader.h
 ./ObjReader.cpp
 ../include/utility.reader.obj.h
)

source_group("" FILES ${source})
add_library(utility.reader.obj ${source} CMakeLists.txt)
target_link_libraries(utility.reader.obj utility.reader.mesh simulation.geometry visualization)
