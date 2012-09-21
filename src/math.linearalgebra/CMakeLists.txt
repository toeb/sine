set(source
 ./Matrix.h
 ./Vector.h
 ./MatrixOperations.h
 ./ScalarOperations.h
 ./VectorOperations.h 
 ./types.h 
 ./types.cpp 
)
source_group("" FILES ${source})


file(GLOB_RECURSE operationsSource 
    "operations/*.h"
    "operations/*.cpp"
)
source_group("operations" FILES ${operationsSource})


set(source ${source} ${operationsSource})
add_library(math.linearalgebra ${source} CMakeLists.txt ../config.h)
#target_link_libraries(math.linearalgebra core)