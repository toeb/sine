set(source 
MeshReader.h
MeshReader.cpp
IMeshBuilder.h
IMeshBuilder.cpp
 ../include/utility.reader.mesh.h
)


source_group("" FILES ${source})
add_library(utility.reader.mesh ${source} CMakeLists.txt)
target_link_libraries(utility.reader.mesh utility.reader)