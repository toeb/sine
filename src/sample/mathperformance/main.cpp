#include <config.h>
#include <core/Time.h>
#include <iostream>
#include <math/matrix2/StaticMatrix.h>
#include <math/matrix2/Quaternion.h>
#include <math/matrix2/specialization/StaticMatrixNxNSpecialization.h>
#include <math/matrix2/specialization/StaticMatrix3x3Specialization.h>
#include <math/matrix2/specialization/StaticMatrix3x1Specialization.h>
#include <math/matrix2/StaticMatrixOperators.h>

#include <math/matrix2/DynamicMatrix.h>
#include <math/matrix2/specialization/DynamicMatrixSpecialization.h>
#include <math/matrix2/DynamicMatrixOperators.h>
#include <string>

#include <algorithm>
#include <math/matrix1/MatrixNxM.h>
#include <math/matrix1/Quaternion.h>
#include <math/matrix1/Matrix3x3.h>
#include <typeinfo>
#include <sstream>
#include <functional>
// //#include <math/definitions.h>
using namespace nspace;
using namespace std;

typedef matrix2::StaticMatrix<Real,3,3> Mat332;
typedef matrix2::Quaternion<Real> Quat2;
typedef matrix2::DynamicMatrix<Real> MatMN2;
typedef Matrix3x3 Mat331;
typedef Quaternion Quat1;
typedef MatrixNxM MatMN1;



class PerformanceTest{
private:
  Time start;
  Time _duration;
  std::string _name;
  int _n;
  static std::vector<PerformanceTest*> tests;
public:
  static void runAll(int n){
    std::for_each(tests.begin(), tests.end(), [n](PerformanceTest * t){
      t->n() =(int) n / t->normalization();
      t->run();
     t->toString(std::cout);
      cout << endl;
    });
  }
  stringstream nameStream;
  void toString(std::ostream & s){
    s <<"t: "<< duration() <<" "<< nameStream.str() << ": n= "<<n();
  }
  int & n(){return _n;};
  void setName(const std::string & name){_name = name;}
  PerformanceTest():_name(""),start(0),_duration(0){

    tests.push_back(this);
  }
  virtual Real normalization(){return 1;}
  Time duration(){return _duration;}
  void tick(){start = systemTime();}
  void tock(){_duration += systemTime()-start;};
  void reset(){tock();_duration =0;}
  void run(){
    for(int i=0; i < n(); i++){
      initTest();
      performTest();
      cleanupTest();
    }
  } 
  virtual void performTest()=0;
  virtual void cleanupTest(){

  } 
  virtual void initTest(){

  }
};
std::vector<PerformanceTest*> PerformanceTest::tests = std::vector<PerformanceTest*>();


template<typename Mat, typename FilterFunction>
class FilterMatrixTest:public PerformanceTest{
private:
  const Mat & a;
  Mat b;
  uint filterWidth;
  uint filterHeight;
  FilterFunction f;
public:
FilterMatrixTest(const Mat & a, FilterFunction f, uint filterWidth, uint filterHeight ):f(f),a(a),filterWidth(filterWidth),filterHeight(filterHeight){
  nameStream<< "FilterMatrixTest "<<" b = f * b "<< typeid(Mat).name();
}
void performTest(){
  tick();
  a.filter(b,f,filterWidth,filterHeight);
  tock();
}
};

template<typename Mat>
class AssignTest : public PerformanceTest{
private:
  Mat a;
  const Mat & b;
public:
  AssignTest(const Mat& b):a(a),b(b){nameStream<< "AssignTest "<<" a = b "<< typeid(Mat).name();}
  
  void performTest(){
    tick();
    a = b;
    tock();
  }
};
template<typename Mat>
class AddTest  : public PerformanceTest{
private:
  Mat c;
  const Mat & a;
  const Mat & b;
public:
  AddTest(const Mat& a, const Mat&b):a(a),b(b){
    nameStream << "AddTest c=a+b "<<typeid(Mat).name();
  }
  void performTest(){
    tick();
   c=a+b;
    tock();
  }
};
template<typename Mat>
class AddInPlaceTest  : public PerformanceTest{
private:
  Mat c;
  const Mat & a;
  const Mat & b;
public:
  AddInPlaceTest(const Mat& a, const Mat&b):a(a),b(b){
    nameStream << "AddInPlaceTest c=a+b "<<typeid(Mat).name();
  }
  void performTest(){
    tick();
    MatrixOps::add(c,a,b);
    tock();
  }
};
template<typename Mat>
class SubtractTest  : public PerformanceTest{
private:
  Mat c;
  const Mat & a;
  const Mat & b;
public:
  SubtractTest(const Mat& a, const Mat&b):a(a),b(b){
    nameStream << "SubtractTest c=a-b "<<typeid(Mat).name();
  }
  void performTest(){
    tick();
    c=a-b;
    tock();
  }
};
template<typename Mat>
class SubtractInPlaceTest  : public PerformanceTest{
private:
  Mat c;
  const Mat & a;
  const Mat & b;
public:
  SubtractInPlaceTest(const Mat& a, const Mat&b):a(a),b(b){
    nameStream << "SubtractInPlaceTest c=a-b "<<typeid(Mat).name();
  }
  void performTest(){
    tick();
    MatrixOps::subtract(c,a,b);
    tock();
  }
};

template<typename Product, typename A, typename B>
class MultMatrixTest  : public PerformanceTest{
private:
  Product c;
  const A & a;
  const B & b;
public:
  MultMatrixTest(const A& a, const B&b):a(a),b(b){
    nameStream << "MultMatrixTest c=a x b "<<typeid(Product).name()<<" = " <<typeid(A).name()<< " * "<<typeid(B).name();
  }
  void performTest(){
    tick();
    c=a*b;
    tock();
  }
};



template<typename Product, typename A, typename B>
class MultMatrixInPlaceTest  : public PerformanceTest{
private:
  Product c;
  const A & a;
  const B & b;
public:
  MultMatrixInPlaceTest(const A& a, const B&b):a(a),b(b){
    nameStream << "MultMatrixInPlaceTest c=a x b "<<typeid(Product).name()<<" = " <<typeid(A).name()<< " * "<<typeid(B).name();
  }
  void performTest(){
    tick();
    MatrixOps::multiplyMatrix(c,a,b);
    tock();
  }
};




template<typename Mat, typename T>
class MultScalarTest  : public PerformanceTest{
private:
  Mat c;
  const Mat & a;
  const T & b;
public:
  MultScalarTest(const Mat & a, const T&b):a(a),b(b){
    nameStream << "MultScalarTest c=a*b "<<typeid(Mat).name()<<" = " <<typeid(Mat).name()<< " * "<<typeid(T).name();
  }
  void performTest(){
    tick();
    c=a*b;
    tock();
  }
};
template<typename Mat, typename T>
class MultScalarInPlaceTest  : public PerformanceTest{
private:
  Mat c;
  const Mat & a;
  const T & b;
public:
  MultScalarInPlaceTest(const Mat & a, const T&b):a(a),b(b){
    nameStream << "MultScalarInPlaceTest c=a*b "<<typeid(Mat).name()<<" = " <<typeid(Mat).name()<< " * "<<typeid(T).name();
  }
  void performTest(){
    tick();
    MatrixOps::multiplyScalar(c,a,b);
    tock();
  }
};
template<typename Mat, typename T>
class ReadElementIJTest: public PerformanceTest{
private:
  const Mat & m;
  T v;
public:
  ReadElementIJTest(const Mat & m):m(m){
    nameStream << "ReadElementIJTest t=m(i,j) "<<typeid(T).name()<<" = " <<typeid(Mat).name()<< "(i,j)";
  }
  void performTest(){
    int rows =m.rows();
    int cols = m.cols();
    
    for(int i = 0; i < rows; i++){
      for(int j=0; j < cols; j++){
        tick();
        v=m(i,j);
        tock();
      }
    }
    
  }
};
template<typename Mat, typename T>
class ReadElementITest: public PerformanceTest{
private:
  const Mat & m;
  T v;
public:
  ReadElementITest(const Mat & m):m(m){
    nameStream << "ReadElementITest t=m(i,j) "<<typeid(T).name()<<" = " <<typeid(Mat).name()<< "(i,j)";
  }
  void performTest(){
    int size = m.size();
    
    for(int j=0; j < size; j++){
      tick();
      v=m(j);
      tock();
    }
    
  }
};
template<typename Mat, typename T>
class WriteElementIJTest: public PerformanceTest{
private:
  Mat m;
  T  v;
public:
  WriteElementIJTest(const T & v):v(v){
    nameStream << "WriteElementIJTest t=m(i,j) "<<typeid(T).name()<<" = " <<typeid(Mat).name()<< "(i,j)";
  }
  void performTest(){
    int rows =m.rows();
    int cols = m.cols();
    for(int i=0; i < rows; i++){
      for(int j=0; j < cols; j++){
        tick();
        m(i,j)=v;
        tock();
      }
    }
    
  }
};
template<typename Mat, typename T>
class WriteElementITest: public PerformanceTest{
private:
  Mat  m;
  T v;
public:
  WriteElementITest(T v):v(v){
    nameStream << "WriteElementITest t=m(i,j) "<<typeid(T).name()<<" = " <<typeid(Mat).name()<< "(i,j)";
  }
  void performTest(){
    int size = m.size();
     for(int j=0; j < size ;j++){
       tick();
       m(j) = v;
       tock();
     }
  }
};
template<typename Quat, typename Rot>
class Quat2RotTest : public PerformanceTest{
private:
  const Quat & q;
  Rot R;
public:
  Quat2RotTest(const Quat & q):q(q){
     nameStream << "Quat2RotTest q->R "<<typeid(Quat).name()<<" -> " <<typeid(Rot).name();
  }
  void performTest(){
    tick();
    q.toRotationMatrix(R);
    tock();
  }
};

template<typename Mat, typename Kernel>
class MatrixConvolutionTest:public PerformanceTest{
private:
  const Mat & a;
  Mat b;
  const Kernel & k;
public:
  MatrixConvolutionTest(const Mat & a, const Kernel & k):k(k),a(a){
    nameStream<< "ConvolveMatrixTest "<<" b = f * b "<< typeid(Mat).name();
  }
  void performTest(){
    tick();
    MatrixOps::convolve(b,a,k);
    tock();
  }
};


template<typename Mat>
class MatrixSymmetricInversionTest:public PerformanceTest{
private:
  const Mat & a;
  Mat b;
public:
  MatrixSymmetricInversionTest(const Mat & a):a(a){
     nameStream << "MatrixSymmetricInversionTest "<<typeid(Mat).name();
  }
  void performTest(){
    tick();
    MatrixOps::invertSymmetricMatrix(b,a);
    tock();
  }
};

template<typename Mat>
class MatrixCompareTest:public PerformanceTest{
  const Mat& a;
  const Mat& b;
  bool result;
public:
  MatrixCompareTest(const Mat& a, const Mat& b):a(a),b(b){
     nameStream << "MatrixCompareTest (aij==bij) for all (aij,bij) "<<typeid(Mat).name();
  }
  void performTest(){
    tick();
    MatrixOps::compareMatrix(result,a,b);
    tock();
  }
};

#define N 100000//10000000

int main(int argc, char ** argv){
  /*
  new AssignTest<nspace::Matrix3x3>(Matrix3x3::Identity());
  new AssignTest<nspace::matrix2::StaticMatrix<Real,3,3>>(nspace::matrix2::StaticMatrix<Real,3,3>::Identity());
  new AssignTest<nspace::Vector3D>(Vector3D::Zero());
  new AssignTest<nspace::matrix2::StaticMatrix<Real,3,1>>(nspace::matrix2::StaticMatrix<Real,3,1>::Zero());
  new AddTest<nspace::Matrix3x3>(Matrix3x3::Identity(), Matrix3x3::Identity());
  new AddTest<nspace::matrix2::StaticMatrix<Real,3,3> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,3>::Identity());
  new AddInPlaceTest<nspace::matrix2::StaticMatrix<Real,3,3> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,3>::Identity());
  
  new SubtractTest<nspace::Matrix3x3>(Matrix3x3::Identity(), Matrix3x3::Identity());
  new SubtractTest<nspace::matrix2::StaticMatrix<Real,3,3> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,3>::Identity());
  new SubtractInPlaceTest<nspace::matrix2::StaticMatrix<Real,3,3> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,3>::Identity());

  new AddTest<nspace::Vector3D>(Vector3D::Ones(), Vector3D::Zero());
  new AddTest<nspace::matrix2::StaticMatrix<Real,3,1> >(nspace::matrix2::StaticMatrix<Real,3,1>::Ones(),nspace::matrix2::StaticMatrix<Real,3,1>::Zero());
  new AddInPlaceTest<nspace::matrix2::StaticMatrix<Real,3,1> >(nspace::matrix2::StaticMatrix<Real,3,1>::Ones(),nspace::matrix2::StaticMatrix<Real,3,1>::Zero());
  
  new SubtractTest<nspace::Vector3D>(Vector3D::Ones(), Vector3D::Zero());
  new SubtractTest<nspace::matrix2::StaticMatrix<Real,3,1> >(nspace::matrix2::StaticMatrix<Real,3,1>::Ones(),nspace::matrix2::StaticMatrix<Real,3,1>::Zero());
  new SubtractInPlaceTest<nspace::matrix2::StaticMatrix<Real,3,1> >(nspace::matrix2::StaticMatrix<Real,3,1>::Ones(),nspace::matrix2::StaticMatrix<Real,3,1>::Zero());


  new MultMatrixTest<nspace::Matrix3x3,nspace::Matrix3x3,nspace::Matrix3x3>(nspace::Matrix3x3::Identity(),nspace::Matrix3x3::Identity());
  new MultMatrixTest<nspace::matrix2::StaticMatrix<Real,3,3>,nspace::matrix2::StaticMatrix<Real,3,3>,nspace::matrix2::StaticMatrix<Real,3,3> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,3>::Identity());
  new MultMatrixInPlaceTest<nspace::matrix2::StaticMatrix<Real,3,3>,nspace::matrix2::StaticMatrix<Real,3,3>,nspace::matrix2::StaticMatrix<Real,3,3> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,3>::Identity());
  
  new MultScalarTest<nspace::Matrix3x3,Real>(nspace::Matrix3x3::Identity(),5.0);
  new MultScalarTest<nspace::matrix2::StaticMatrix<Real,3,3>,Real>(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),5.0);
  new MultScalarInPlaceTest<nspace::matrix2::StaticMatrix<Real,3,3>,Real>(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),5.0);

  
  new MultMatrixTest<nspace::Vector3D,nspace::Matrix3x3,nspace::Vector3D>(nspace::Matrix3x3::Identity(),nspace::Vector3D::Zero());
  new MultMatrixTest<nspace::matrix2::StaticMatrix<Real,3,1>,nspace::matrix2::StaticMatrix<Real,3,3>,nspace::matrix2::StaticMatrix<Real,3,1> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,1>::Ones());
  new MultMatrixInPlaceTest<nspace::matrix2::StaticMatrix<Real,3,1>,nspace::matrix2::StaticMatrix<Real,3,3>,nspace::matrix2::StaticMatrix<Real,3,1> >(nspace::matrix2::StaticMatrix<Real,3,3>::Identity(),nspace::matrix2::StaticMatrix<Real,3,1>::Ones());

  new Quat2RotTest<nspace::Quaternion, nspace::Matrix3x3>(Quaternion::ZeroRotation());
  new Quat2RotTest<nspace::matrix2::Quaternion<Real>, nspace::matrix2::StaticMatrix<Real,3,3>>(nspace::matrix2::Quaternion<Real>::ZeroRotation());

  new MultScalarTest<nspace::MatrixNxM,Real>(*new nspace::MatrixNxM(50,2),5.0);
  new MultScalarTest<nspace::matrix2::DynamicMatrix<Real>,Real>(*new nspace::matrix2::DynamicMatrix<Real>(50,2),5.0);
  new MultScalarInPlaceTest<nspace::matrix2::DynamicMatrix<Real>,Real>(*new nspace::matrix2::DynamicMatrix<Real>(50,2),5.0);

  new AddTest<nspace::MatrixNxM>(*new nspace::MatrixNxM(50,2),*new nspace::MatrixNxM(50,2));
  new AddTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(50,2),*new nspace::matrix2::DynamicMatrix<Real>(50,2));
  new AddInPlaceTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(50,2),*new nspace::matrix2::DynamicMatrix<Real>(50,2));

  new SubtractTest<nspace::MatrixNxM>(*new nspace::MatrixNxM(50,2),*new nspace::MatrixNxM(50,2));
  new SubtractTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(50,2),*new nspace::matrix2::DynamicMatrix<Real>(50,2));
  new SubtractInPlaceTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(50,2),*new nspace::matrix2::DynamicMatrix<Real>(50,2));
  
  int nHigh=1001;
  
  new MultScalarTest<nspace::MatrixNxM,Real>(*new nspace::MatrixNxM(nHigh,2),5.0);
  new MultScalarTest<nspace::matrix2::DynamicMatrix<Real>,Real>(*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2),5.0);
  new MultScalarInPlaceTest<nspace::matrix2::DynamicMatrix<Real>,Real>(*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2),5.0);

  new AddTest<nspace::MatrixNxM>(*new nspace::MatrixNxM(nHigh,2),*new nspace::MatrixNxM(nHigh,2));
  new AddTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2),*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2));
  new AddInPlaceTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2),*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2));

  new SubtractTest<nspace::MatrixNxM>(*new nspace::MatrixNxM(nHigh,2),*new nspace::MatrixNxM(nHigh,2));
  new SubtractTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2),*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2));
  new SubtractInPlaceTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2),*new nspace::matrix2::DynamicMatrix<Real>(nHigh,2));
  
  new WriteElementIJTest<Mat332,Real>(3.0);
  new WriteElementIJTest<Mat331,Real>(3.0);

  new WriteElementITest<Mat332,Real>(3.0);
  new WriteElementITest<Mat331,Real>(3.0);

  new ReadElementIJTest<Mat332,Real>(Mat332::Identity());
  new ReadElementIJTest<Mat331,Real>(Mat331::Identity());

  new ReadElementITest<Mat332,Real>(Mat332::Identity());
  new ReadElementITest<Mat331,Real>(Mat331::Identity());

  new FilterMatrixTest<MatMN2,std::function<void (Real &, MatMN2 & ) > >(*new MatMN2(512,512),
    [](Real & v, MatMN2 & window){
     v=0.0;
},3,3);
 //*/

  //new MatrixConvolutionTest<MatMN2,MatMN2>(*new MatMN2(4096,4096),*new MatMN2(7,7));
  //new MatrixSymmetricInversionTest<Mat332>(Mat332::Identity());
  new MatrixCompareTest<Mat332>(Mat332::Identity(),Mat332::Identity());
  PerformanceTest::runAll(100000000);
  //quat2RotMatrix<Quat2,Mat332,N>();
  //quat2RotMatrix<Quat1,Mat331,N>();
  //quatGetRot<Quat2,Mat332,N>();
  //quatGetRot<Quat1,Mat331,N>();
  //dynamicCopyMat<MatMN2,N,1000,1000>();
  //dynamicCopyMat<MatMN1,N,1000,1000>();
  //dynamicAddMat<MatMN2,N,1000,1000>();
  //dynamicAddMat<MatMN1,N,1000,1000>();
//   dynamicSetConstant<MatMN2,N,1,1>();
//   dynamicSetConstant<MatMN1,N,1,1>();
//   dynamicSetFunction<MatMN2,N,20,1>();
//    dynamicSetFunction<MatMN1,N,20,1>();
//   dynamicMultScalarMat<MatMN2,N,2000000,1>();
//   dynamicMultScalarMat<MatMN2,N,2000000,1>();
//   dynamicMultScalarMat<MatMN2,N,2000000,1>();
//   dynamicMultScalarMat<MatMN1,N,2000000,1>();
//   dynamicMultScalarMat<MatMN1,N,2000000,1>();
//   dynamicMultScalarMat<MatMN1,N,2000000,1>();
  return 0;
}