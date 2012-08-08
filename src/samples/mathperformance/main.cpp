#include <common/Config.h>
#include <common/Time.h>
#include <iostream>
#include <math/matrix2/StaticMatrix.h>
#include <math/matrix2/Quaternion.h>
#include <math/matrix2/StaticMatrixSpecialization.h>
#include <math/matrix2/StaticMatrixOperators.h>
#include <math/matrix2/DynamicMatrix.h>
#include <string>

#include <algorithm>
#include <math/matrix1/MatrixNxM.h>
#include <math/matrix1/Quaternion.h>
#include <math/matrix1/Matrix3x3.h>
#include <typeinfo>
#include <sstream>
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
      t->n() =n / t->normalization();
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
  virtual int normalization(){return 1;}
  Time duration(){return _duration;}
  void tick(){start = systemTime();}
  void tock(){_duration += systemTime()-start;};
  void reset(){tock();_duration =0;}
  virtual void run(){

  }
};
std::vector<PerformanceTest*> PerformanceTest::tests = std::vector<PerformanceTest*>();

template<typename Mat>
class AssignTest : public PerformanceTest{
private:
  Mat a;
  const Mat & b;
public:
  AssignTest(const Mat& b):a(a),b(b){nameStream<< "AssignTest "<<" a = b "<< typeid(Mat).name();}
  
  void run(){
    tick();
    for(int i=0; i< n(); i++) a = b;
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)c=a+b;
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)MatrixOps::add(c,a,b);
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)c=a-b;
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)MatrixOps::subtract(c,a,b);
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)c=a*b;
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)MatrixOps::multiplyMatrix(c,a,b);
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)c=a*b;
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
  void run(){
    tick();
    for(int i=0; i < n(); i++)MatrixOps::multiplyScalar(c,a,b);
    tock();
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
  void run(){
    tick();
    for(int i=0; i < n(); i++) q.toRotationMatrix(R);
    tock();
  }
};


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
template<typename Mat,int n, int rows, int cols>
void dynamicMultScalarMat(){
  std::cout<< "dynamicMultScalarMat n="<<n;
  Mat m1;
  m1.resize(rows,cols);
  Mat m2;
  Time start = systemTime();
  for(int i=0; i < n; i++){
    m2= 0.5*m1;
  }
  Time end = systemTime();
  cout << " took: "<<(end-start)<<" seconds"<<endl;
};
template<typename Mat,int n, int rows, int cols>
void dynamicSetConstant(){
  std::cout<< "dynamicSetConstant n="<<n;
  Mat m1;
  m1.resize(rows,cols);
  
  Time start = systemTime();
  for(int i=0; i < n; i++){
    m1.setConstant((double)i);
  }
  Time end = systemTime();
  cout << " took: "<<(end-start)<<" seconds"<<endl;
};

template<typename Mat,int n, int rows, int cols>
void dynamicSetFunction(){
  std::cout<< "dynamicSetFunction n="<<n;
  Mat m1;
  m1.resize(rows,cols);

  Time start = systemTime();
  for(int i=0; i < n; i++){
    m1.setFunction([](Real & val, int i, int j){val = i+j;});
  }
  Time end = systemTime();
  cout << " took: "<<(end-start)<<" seconds"<<endl;
};


#define N 100000//10000000

int main(int argc, char ** argv){
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
  
  
  new MultScalarTest<nspace::MatrixNxM,Real>(*new nspace::MatrixNxM(10000,2),5.0);
  new MultScalarTest<nspace::matrix2::DynamicMatrix<Real>,Real>(*new nspace::matrix2::DynamicMatrix<Real>(10000,2),5.0);
  new MultScalarInPlaceTest<nspace::matrix2::DynamicMatrix<Real>,Real>(*new nspace::matrix2::DynamicMatrix<Real>(10000,2),5.0);

  new AddTest<nspace::MatrixNxM>(*new nspace::MatrixNxM(10000,2),*new nspace::MatrixNxM(10000,2));
  new AddTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(10000,2),*new nspace::matrix2::DynamicMatrix<Real>(10000,2));
  new AddInPlaceTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(10000,2),*new nspace::matrix2::DynamicMatrix<Real>(10000,2));

  new SubtractTest<nspace::MatrixNxM>(*new nspace::MatrixNxM(10000,2),*new nspace::MatrixNxM(10000,2));
  new SubtractTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(10000,2),*new nspace::matrix2::DynamicMatrix<Real>(10000,2));
  new SubtractInPlaceTest<nspace::matrix2::DynamicMatrix<Real>>(*new nspace::matrix2::DynamicMatrix<Real>(10000,2),*new nspace::matrix2::DynamicMatrix<Real>(10000,2));



  PerformanceTest::runAll(N);
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