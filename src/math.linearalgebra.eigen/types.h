#pragma once
#include <math.linearalgebra/MatrixOperations.h>
#include <Eigen/Core>
#include <Eigen/Geometry>


namespace nspace{
namespace math{
namespace eigen{
		
typedef Eigen::Matrix<Real,Eigen::Dynamic,Eigen::Dynamic> MatrixNxM;
typedef Eigen::Matrix<Real,3,3> Matrix3x3;
typedef Eigen::Matrix<Real,2,2> Matrix2x2;
typedef Eigen::Matrix<Real,3,2> Matrix3x2;
typedef Eigen::Matrix<Real,2,3> Matrix2x3;
typedef Eigen::Matrix<Real,3,1> Vector3D;
typedef Eigen::Matrix<Real,2,1> Vector2D;
typedef Eigen::Matrix<Real,1,1> Vector1D;
typedef Eigen::Matrix<Real,4,4> Matrix4x4;
typedef Eigen::Matrix<Real,4,3> Matrix4x3;
typedef Eigen::Matrix<Real,3,4> Matrix3x4;
typedef Eigen::Matrix<Real,Eigen::Dynamic,1> VectorND;
typedef Eigen::Quaternion<Real> Quaternion;

}
}
}