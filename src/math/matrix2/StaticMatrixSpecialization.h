#pragma once

#include <math/MatrixOperations.h>
namespace nspace{
  /**
 * \brief specialization for the 3x3 Matrix Product
 *
 * \return .
 */
template<>
inline void MatrixMultiplication<Real, matrix2::StaticMatrix<Real,3,3> ,matrix2::StaticMatrix<Real,3,3> ,matrix2::StaticMatrix<Real,3,3> >::multiply(
  matrix2::StaticMatrix<Real,3,3> &mC,const matrix2::StaticMatrix<Real,3,3> &mA,const matrix2::StaticMatrix<Real,3,3> &mB
  ){
    const Real * a=mA.data();
    const Real * b=mB.data();
    Real * c=mC.data();
    c[0]= a[0]*b[0]+a[1]*b[3]+a[2]*b[6];
    c[1]= a[0]*b[1]+a[1]*b[4]+a[2]*b[7];
    c[2]= a[0]*b[2]+a[1]*b[5]+a[2]*b[8];
    c[3]= a[3]*b[0]+a[4]*b[3]+a[5]*b[6];
    c[4]= a[3]*b[1]+a[4]*b[4]+a[5]*b[7];
    c[5]= a[3]*b[2]+a[4]*b[5]+a[5]*b[8];
    c[6]= a[6]*b[0]+a[7]*b[3]+a[8]*b[6];
    c[7]= a[6]*b[1]+a[7]*b[4]+a[8]*b[7];
    c[8]= a[6]*b[2]+a[7]*b[5]+a[8]*b[8];
}

/**
 * \brief specialization for the 3D MatrixVector Product
 *
 * \return .
 */
template<>
inline void MatrixMultiplication<Real, matrix2::StaticMatrix<Real,3,1> ,matrix2::StaticMatrix<Real,3,3> ,matrix2::StaticMatrix<Real,3,1> >::multiply(
  matrix2::StaticMatrix<Real,3,1> &mC,const matrix2::StaticMatrix<Real,3,3> &mA,const matrix2::StaticMatrix<Real,3,1> &mB
  ){
    const Real * a=mA.data();
    const Real * b=mB.data();
    Real * c=mC.data();
    c[0]= a[0]*b[0]+a[3]*b[1]+a[6]*b[2];
    c[1]= a[1]*b[0]+a[4]*b[1]+a[7]*b[2];
    c[2]= a[2]*b[0]+a[5]*b[1]+a[8]*b[2];    
}
}