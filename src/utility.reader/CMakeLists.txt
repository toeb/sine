set(source
 ./Reader.h
 ./Reader.cpp
)

add_library(utility.reader ${source} CMakeLists.txt)
source_group("" FILES ${source})
target_link_libraries(utility.reader common)