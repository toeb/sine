set(source 
./types.h
./types.cpp
)
source_group("" FILES ${source})
add_library(math.linearalgebra.eigen
 ${source}
 CMakeLists.txt
 ../config.h
)
target_link_libraries(math.linearalgebra.eigen math.linearalgebra math.linearalgebra.dslib)