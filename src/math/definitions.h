#pragma once
#include <core/Config.h>


#define EPSILON 1.0E-9
#define PI 3.14159  

#define MATRIX_CLASSES 2

#if MATRIX_CLASSES ==1 


#include <math/matrix1/Vector3D.h>
#include <math/matrix1/VectorND.h>
#include <math/matrix1/MatrixNxM.h>
#include <math/matrix1/Matrix3x3.h>
#include <math/matrix1/Quaternion.h>
#include <math/matrix1/Matrix4x3.h>
#include <math/matrix1/Matrix4x4.h>
#include <math/matrix1/Vector2D.h>

#elif MATRIX_CLASSES == 2

#include <math/matrix2/DynamicMatrix.h>
#include <math/matrix2/specialization/DynamicMatrixSpecialization.h>
#include <math/matrix2/DynamicMatrixOperators.h>


#include <math/matrix2/StaticMatrix.h>
#include <math/matrix2/specialization/StaticMatrixNxNSpecialization.h>
#include <math/matrix2/specialization/StaticMatrix3x3Specialization.h>
#include <math/matrix2/specialization/StaticMatrix3x1Specialization.h>
#include <math/matrix2/StaticMatrixOperators.h>


#include <math/matrix2/Quaternion.h>
#include <math/matrix2/specialization/QuaternionSpecialization.h>
#include <math/matrix2/QuaternionOperators.h>
namespace nspace{
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
#elif MATRIX_CLASSES == 3
#include <Eigen/Core>
namespace nspace{
typedef Eigen::Matrix<Real,Eigen::Dynamic,Eigen::Dynamic> MatrixNxM;
typedef Eigen::Matrix<Real,3,3> Matrix3x3;
typedef Eigen::Quaternion<Real> Quaternion;
typedef Eigen::Matrix<Real,3,1> Vector3D;
typedef Eigen::Matrix<Real,4,4> Matrix4x4;
typedef Eigen::Matrix<Real,Eigen::Dynamic,1> VectorND;
}
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
