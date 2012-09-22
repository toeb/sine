set(source 
types.h
types.cpp
DynamicMatrix.h
DynamicMatrixOperators.h
MatrixBase.h
Quaternion.h
QuaternionOperators.h
StaticMatrix.h
StaticMatrixOperators.h
core.h
)
source_group("" FILES ${source})

set(specializationSource
 ./specialization/DynamicMatrixSpecialization.h
 ./specialization/QuaternionSpecialization.h
 ./specialization/StaticMatrix3x1Specialization.h
 ./specialization/StaticMatrix3x3Specialization.h
 ./specialization/StaticMatrixNxNSpecialization.h
)
source_group("specialization" FILES ${specializationSource})

set(source ${source} ${specializationSource})
add_library(math.matrix.dslib ${source} CMakeLists.txt ../config.h)
target_link_libraries(math.matrix.dslib math.matrix)