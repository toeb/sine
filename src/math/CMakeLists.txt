set(typesSource
	./types/Matrix.h
	./types/Matrix2x2.cpp
	./types/Matrix2x2.h
	./types/Matrix2x3.cpp
	./types/Matrix2x3.h
	./types/Matrix3x2.cpp
	./types/Matrix3x2.h
	./types/Matrix3x3.cpp
	./types/Matrix3x3.h
	./types/Matrix4x4.cpp
	./types/Matrix4x4.h
	./types/Matrix4x3.cpp
	./types/Matrix4x3.h
	./types/MatrixNxM.cpp
	./types/MatrixNxM.h
	./types/Quaternion.cpp
	./types/Quaternion.h
	./types/Vector.h
	./types/Vector1D.cpp
	./types/Vector1D.h
	./types/Vector2D.cpp
	./types/Vector2D.h
	./types/Vector3D.cpp
	./types/Vector3D.h
	./types/VectorND.cpp
	./types/VectorND.h
)
set(source
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
)
source_group("src" FILES ${source})
source_group("src\\types" FILES ${typesSource})
add_library(math ${source} ${typesSource} CMakeLists.txt )
target_link_libraries(math common)
project_folder("" math)
#SET_TARGET_PROPERTIES(math PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE ${IBDS_STATIC_LIBRARY_FLAGS_RELEASE})   


