
ADD_LIBRARY(Math
      ../Common/Config.h
	  CDMath.cpp
	  CDMath.h
      MathDefs.h
      Matrix.h
      Matrix2x2.cpp
      Matrix2x2.h
      Matrix2x3.cpp
      Matrix2x3.h
      Matrix3x2.cpp
      Matrix3x2.h
      Matrix3x3.cpp
      Matrix3x3.h
      Matrix4x4.cpp
      Matrix4x4.h
      MatrixNxM.cpp
      MatrixNxM.h
      Quaternion.cpp
      Quaternion.h
      SimMath.cpp
      SimMath.h
      Vector.h
      Vector1D.cpp
      Vector1D.h
      Vector2D.cpp
      Vector2D.h
      Vector3D.cpp
      Vector3D.h
      VectorND.cpp
      VectorND.h
	  
	  CMakeLists.txt
)

SET_TARGET_PROPERTIES(Math PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE ${IBDS_STATIC_LIBRARY_FLAGS_RELEASE})   


