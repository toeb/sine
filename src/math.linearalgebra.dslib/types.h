#pragma once

#include <math.linearalgebra.dslib/DynamicMatrix.h>
#include <math.linearalgebra.dslib/specialization/DynamicMatrixSpecialization.h>
#include <math.linearalgebra.dslib/DynamicMatrixOperators.h>


#include <math.linearalgebra.dslib/StaticMatrix.h>
#include <math.linearalgebra.dslib/specialization/StaticMatrixNxNSpecialization.h>
#include <math.linearalgebra.dslib/specialization/StaticMatrix3x3Specialization.h>
#include <math.linearalgebra.dslib/specialization/StaticMatrix3x1Specialization.h>
#include <math.linearalgebra.dslib/StaticMatrixOperators.h>


#include <math.linearalgebra.dslib/Quaternion.h>
#include <math.linearalgebra.dslib/specialization/QuaternionSpecialization.h>
#include <math.linearalgebra.dslib/QuaternionOperators.h>
namespace nspace{
namespace math{
namespace dslib{
  typedef matrix2::StaticMatrix<Real,2,1> Vector2D;
  typedef matrix2::StaticMatrix<Real,3,1> Vector3D;
  typedef matrix2::StaticMatrix<Real, 3,3> Matrix3x3;
  typedef matrix2::StaticMatrix<Real, 2,2> Matrix2x2;
  typedef matrix2::StaticMatrix<Real, 4,4> Matrix4x4;
  typedef matrix2::StaticMatrix<Real, 4,3> Matrix4x3;
  typedef matrix2::StaticMatrix<Real, 3,4> Matrix3x4;
  typedef matrix2::Quaternion<Real> Quaternion;
  typedef matrix2::DynamicMatrix<Real> VectorND;
  typedef matrix2::DynamicMatrix<Real> MatrixNxM;
}
}
}