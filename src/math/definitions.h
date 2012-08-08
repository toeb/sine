#pragma once
#include <common/Config.h>
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

#include <math/matrix2/StaticMatrix.h>
#include <math/matrix2/DynamicMatrix.h>
#include <math/matrix2/StaticMatrixOperators.h>
#include <math/matrix2/StaticMatrixSpecialization.h>
#include <math/matrix2/Quaternion.h>

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

typedef int MatrixNxM;
typedef int Matrix3x3;
typedef int Quaternion;
typedef int Vector3D;
typedef int Matrix4x4;
typedef int VectorND;
using namespace nspace::matrix3;
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif