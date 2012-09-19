set(source
 ./Reader.h
 ./Reader.cpp
)

add_library(reader ${source} CMakeLists.txt)
source_group("" FILES ${source})
project_folder("utility" reader)
