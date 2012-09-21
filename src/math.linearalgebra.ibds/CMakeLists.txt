set (source
./Matrix2x2.cpp
./Matrix2x2.h
./Matrix2x3.cpp
./Matrix2x3.h
./Matrix3x2.cpp
./Matrix3x2.h
./Matrix3x3.cpp
./Matrix3x3.h
./Matrix4x4.cpp
./Matrix4x4.h
./Matrix4x3.cpp
./Matrix4x3.h
./MatrixNxM.cpp
./MatrixNxM.h
./Quaternion.cpp
./Quaternion.h
./Vector1D.cpp
./Vector1D.h
./Vector2D.cpp
./Vector2D.h
./Vector3D.cpp
./Vector3D.h
./VectorND.cpp
./VectorND.h
./StaticMatrix.h
./DynamicMatrix.h
./types.h
./types.cpp
)

source_group("" FILES ${source})

add_library(math.linearalgebra.ibds ${source} CMakeLists.txt ../config.h)
target_link_libraries(math.linearalgebra.ibds math.linearalgebra)