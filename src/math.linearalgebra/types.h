#pragma once
#include <config.h>

#if MATRIX_CLASSES ==1 

#elif MATRIX_CLASSES == 2
#include <math.linearalgebra.dslib/types.h>

namespace nspace{
typedef nspace::math::dslib::Vector2D   Vector2D;
typedef nspace::math::dslib::Vector3D   Vector3D;
typedef nspace::math::dslib::Matrix3x3  Matrix3x3;
typedef nspace::math::dslib::Matrix2x2  Matrix2x2;
typedef nspace::math::dslib::Matrix4x4  Matrix4x4;
typedef nspace::math::dslib::Matrix4x3  Matrix4x3;
typedef nspace::math::dslib::Matrix3x4  Matrix3x4;
typedef nspace::math::dslib::Quaternion Quaternion;
typedef nspace::math::dslib::VectorND   VectorND;
typedef nspace::math::dslib::MatrixNxM  MatrixNxM;
}
#elif MATRIX_CLASSES == 3
#include <math.linearalgebra.dslib/types.h>
#include <math.linearalgebra.eigen/types.h>

namespace nspace{
  typedef nspace::math::eigen::Vector2D   Vector2D;
  typedef nspace::math::eigen::Vector3D   Vector3D;
  typedef nspace::math::eigen::Matrix3x3  Matrix3x3;
  typedef nspace::math::eigen::Matrix2x2  Matrix2x2;
  typedef nspace::math::eigen::Matrix4x4  Matrix4x4;
  typedef nspace::math::eigen::Matrix4x3  Matrix4x3;
  typedef nspace::math::eigen::Matrix3x4  Matrix3x4;
  typedef nspace::math::dslib::Quaternion Quaternion;
  typedef nspace::math::eigen::VectorND   VectorND;
  typedef nspace::math::eigen::MatrixNxM  MatrixNxM;
}
#endif

