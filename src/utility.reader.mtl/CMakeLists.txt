set(source
 ./MtlReader.h
 ./MtlReader.cpp
 ../include/utility.reader.mtl.h
)

add_library(utility.reader.mtl ${source} CMakeLists.txt)
source_group("" FILES ${source})
target_link_libraries(utility.reader.mtl utility.reader visualization)