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

set(operationsSource
./operations/MatrixAdditionInPlace.h
./operations/MatrixAddition.h
./operations/MatrixAssignment.h
./operations/MatrixConvolution.h
./operations/MatrixFilter.h
./operations/MatrixFrobeniusNorm.h
./operations/MatrixInversion.h
./operations/MatrixMinimumElement.h
./operations/MatrixMaximumElement.h
./operations/MatrixMultiplicationInPlace.h
./operations/MatrixMultiplication.h
./operations/MatrixNegationInPlace.h
./operations/MatrixNegation.h
./operations/MatrixNormalization.h
./operations/MatrixMultiplication.h
./operations/MatrixAllocate.h
./operations/MatrixDeallocate.h
./operations/MatrixAccessElement.h
./operations/MatrixScalarDivisionInPlace.h
./operations/MatrixScalarDivision.h
./operations/MatrixScalarAddition.h
./operations/MatrixScalarSubtraction.h
./operations/MatrixScalarMultiplicationInPlace.h
./operations/MatrixScalarMultiplication.h
./operations/MatrixSetConstant.h
./operations/MatrixSetFunction.h
./operations/MatrixSubtractionInPlace.h
./operations/MatrixSubtraction.h
./operations/MatrixInversionSymmetric.h
./operations/MatrixTranspositionInPlace.h
./operations/MatrixTransposition.h
./operations/VectorCrossProduct.h
./operations/VectorInnerProduct.h
./operations/VectorOuterProduct.h
./operations/VectorToCrossProductMatrix.h
./operations/QuaternionMultiplication.h
./operations/QuaternionMultiplicationScalar.h
./operations/QuaternionConjugation.h
./operations/QuaternionToRotationMatrix.h
./operations/MatrixElementWiseMultiplication.h
./operations/MatrixElementWiseDivision.h
./operations/MatrixElementWiseBinaryOperation.h
./operations/MatrixElementWiseUnaryOperation.h
./operations/MatrixBlockExtract.h
./operations/MatrixBlockAssign.h
./operations/MatrixReduce.h
./operations/MatrixReduceSum.h
./operations/MatrixCompare.h
)


source_group("operations" FILES ${operationsSource})


set(source ${source} ${operationsSource})
add_library(math.linearalgebra ${source} CMakeLists.txt ../config.h)
#target_link_libraries(math.linearalgebra core)