set(source 
PngReader.h
PngReader.cpp
 ../include/utility.reader.png.h
)


source_group("" FILES ${source})
add_library(utility.reader.png ${source} CMakeLists.txt)
target_link_libraries(utility.reader.png utility.reader utility.imaging)