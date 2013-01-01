
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
 ./Index.h
 ./CMakeLists.txt 
 ./functional/MatrixFunction.h
 ../config.h
 ../include/math.matrix.h
)
source_group("" FILES ${source})

set(specializationsSource
./specialization/Array1D.h
./specialization/Scalars.h
./specialization/StdVector.h

)
source_group("specialization" FILES ${specializationsSource})
set(source ${source} ${specializationsSource})

file(GLOB_RECURSE operationsSource 
    "operations/*.h"
    "operations/*.cpp"
)
source_group("operations" FILES ${operationsSource})
set(source ${source} ${operationsSource})

add_library(math.matrix ${source} )
target_link_libraries(math.matrix math.operation)