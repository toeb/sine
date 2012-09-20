set(source 
 ./ObjMeshReader.h
 ./ObjMeshReader.cpp
)


source_group("" FILES ${source})
add_library(utility.reader.obj ${source} CMakeLists.txt)
target_link_libraries(utility.reader.obj utility.reader simulation.geometry)
