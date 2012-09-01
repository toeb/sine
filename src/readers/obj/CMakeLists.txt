set(source 
 ./ObjMeshReader.h
 ./ObjMeshReader.cpp
)


source_group("" FILES ${source})
add_library(obj ${source} CMakeLists.txt)
project_folder("readers" obj)
