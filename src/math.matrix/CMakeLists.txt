set(source
 ./Matrix.h
 ./Vector.h
 ./Quaternion.h
 ./MatrixOperations.h
 ./MatrixOperators.h
 ./VectorOperations.h 
 ./VectorOperators.h
 ./QuaternionOperations.h
 ./QuaternionOperators.h
 ./core.h
 ./types.h 
 ./types.cpp 
 ./CMakeLists.txt 
 ../config.h
)
source_group("" FILES ${source})

file(GLOB_RECURSE operationsSource 
    "operations/*.h"
    "operations/*.cpp"
)
source_group("operations" FILES ${operationsSource})


set(source ${source} ${operationsSource})
add_library(math.matrix ${source} )
target_link_libraries(math.matrix math.operation)