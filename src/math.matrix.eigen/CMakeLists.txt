set(source 
./types.h
./types.cpp
./core.h
)
source_group("" FILES ${source})
add_library(math.matrix.eigen
 ${source}
 CMakeLists.txt
 ../config.h
)
target_link_libraries(math.matrix.eigen math.matrix math.matrix.dslib)