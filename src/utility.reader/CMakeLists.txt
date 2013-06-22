set(source
 ./Reader.h
 ./Reader.cpp
 ./Writer.h
 ./Writer.cpp
 ../include/utility.reader.h
)

add_library(utility.reader ${source} CMakeLists.txt)
source_group("" FILES ${source})
target_link_libraries(utility.reader core core.task)