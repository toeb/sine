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
./operations/QuaternionConjugation.h
./operations/QuaternionToRotationMatrix.h
)
source_group("operations" FILES ${operationsSource})
set(matrix1Source
	./matrix1/Matrix2x2.cpp
	./matrix1/Matrix2x2.h
	./matrix1/Matrix2x3.cpp
	./matrix1/Matrix2x3.h
	./matrix1/Matrix3x2.cpp
	./matrix1/Matrix3x2.h
	./matrix1/Matrix3x3.cpp
	./matrix1/Matrix3x3.h
	./matrix1/Matrix4x4.cpp
	./matrix1/Matrix4x4.h
	./matrix1/Matrix4x3.cpp
	./matrix1/Matrix4x3.h
	./matrix1/MatrixNxM.cpp
	./matrix1/MatrixNxM.h
	./matrix1/Quaternion.cpp
	./matrix1/Quaternion.h
	./matrix1/Vector1D.cpp
	./matrix1/Vector1D.h
	./matrix1/Vector2D.cpp
	./matrix1/Vector2D.h
	./matrix1/Vector3D.cpp
	./matrix1/Vector3D.h
	./matrix1/VectorND.cpp
	./matrix1/VectorND.h
	./matrix1/StaticMatrix.h
	./matrix1/DynamicMatrix.h
)
source_group("matrix1" FILES ${matrix1Source})
set(matrix2Source
 ./matrix2/DynamicMatrix.h
 ./matrix2/Quaternion.h
 ./matrix2/StaticMatrix.h
 ./matrix2/StaticMatrixOperators.h
 ./matrix2/StaticMatrixSpecialization.h
)
source_group("matrix2" FILES ${matrix2Source})
set(matrix3Source 
	./matrix3/DynamicMatrix.h
	
)
source_group("matrix3" FILES ${matrix3Source})

set(source
    ./Matrix.h
	./Vector.h
	./definitions.h
	./CDMath.cpp
	./CDMath.h
	./MathDefs.h
	./SimMath.cpp
	./SimMath.h
	./IAverage.h
	./IAverage.cpp
	./Average.h
	./Average.cpp
	./AverageRate.h
	./AverageRate.cpp
	./AverageOverTime.h
	./AverageOverTime.cpp
	./Statistics.h
	./Statistics.cpp
	./ScalarOperations.h
	./VectorOperations.h
	./MatrixOperations.h
	
)
source_group("src" FILES ${source})

add_library(math ${source} ${matrix1Source} ${matrix2Source} ${matrix3Source} ${operationsSource} CMakeLists.txt )
target_link_libraries(math common)
project_folder("" math)
#SET_TARGET_PROPERTIES(math PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE ${IBDS_STATIC_LIBRARY_FLAGS_RELEASE})   


