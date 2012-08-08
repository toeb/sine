#include <common/Config.h>
#include <common/Time.h>
#include <iostream>
#include <math/matrix2/StaticMatrix.h>
#include <math/matrix2/Quaternion.h>
#include <math/matrix2/StaticMatrixSpecialization.h>
#include <math/matrix2/StaticMatrixOperators.h>
#include <math/matrix2/DynamicMatrix.h>

#include <math/matrix1/MatrixNxM.h>
#include <math/matrix1/Quaternion.h>
#include <math/matrix1/Matrix3x3.h>

// //#include <math/definitions.h>
using namespace nspace;
using namespace std;

typedef matrix2::StaticMatrix<Real,3,3> Mat332;
typedef matrix2::Quaternion<Real> Quat2;
typedef matrix2::DynamicMatrix<Real> MatMN2;
typedef Matrix3x3 Mat331;
typedef Quaternion Quat1;
typedef MatrixNxM MatMN1;

template<typename Quat, typename Mat, int n>
void quat2RotMatrix(){
  std::cout<< "quat2rot n="<<n;
  Time start = systemTime();

  Quat q;
  Mat m;
  for(int i=0; i < n; i++){
    q.toRotationMatrix(m);
  }

  Time end = systemTime();
  cout << " took: "<<(end-start)<<" seconds"<<endl;
};
template<typename Quat, typename Mat,int n>
void quatGetRot(){
  std::cout<< "quatgetrot n="<<n;
  Time start = systemTime();

  Quat q;
  Mat m;
  for(int i=0; i < n; i++){
    m = q.rotationMatrix();
  }

  Time end = systemTime();
  cout << " took: "<<(end-start)<<" seconds"<<endl;
};
template<typename Mat,int n, int rows, int cols>
void dynamicCopyMat(){
  std::cout<< "dynamicCopyMat n="<<n;
  Mat m1;
  m1.resize(rows,cols);
  Mat m2;
  m2.resize(rows,cols);
  Time start = systemTime();

  
  for(int i=0; i < n; i++){
   m1 = m2;
  }

  Time end = systemTime();
  cout << " took: "<<(end-start)<<" seconds"<<endl;
};
template<typename Mat,int n, int rows, int cols>
void dynamicAddMat(){
  std::cout<< "dynamicAddMat n="<<n;
  Mat m1;
  m1.resize(rows,cols);
  Mat m2;
  m2.resize(rows,cols);
  Mat m3;
  Time start = systemTime();


  for(int i=0; i < n; i++){
    m3= m1 + m2;
  }

  Time end = systemTime();
  cout << " took: "<<(end-start)<<" seconds"<<endl;
};
#define N 100

int main(int argc, char ** argv){
  //quat2RotMatrix<Quat2,Mat332,N>();
  //quat2RotMatrix<Quat1,Mat331,N>();
  //quatGetRot<Quat2,Mat332,N>();
  //quatGetRot<Quat1,Mat331,N>();
  //dynamicCopyMat<MatMN2,N,1000,1000>();
  //dynamicCopyMat<MatMN1,N,1000,1000>();
  dynamicAddMat<MatMN2,N,1000,1000>();
  dynamicAddMat<MatMN1,N,1000,1000>();

  return 0;
}