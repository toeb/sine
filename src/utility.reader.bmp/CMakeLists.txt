set(source 
BmpReader.h
BmpReader.cpp
 ../include/utility.reader.bmp.h
)


source_group("" FILES ${source})
add_library(utility.reader.bmp ${source} CMakeLists.txt)
target_link_libraries(utility.reader.bmp utility.reader utility.imaging)