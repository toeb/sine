#include <CppUnitLite/TestHarness.h>
#include <string>
#include <math.matrix/types.h>
#include <core.logging.h>
#include <core.task.h>
#include <core/Serialization.h>
#include <math.matrix.h>

namespace nspace{
  TEST(1, OperationMatrixElementWiseUnary){
    double a[3]={9,81,64};
    elementWiseSquareRootInPlace(a);
    CHECK(a[0]==3&&a[1]==9&&a[2]==8);
  }
  TEST(2, OperationMatrixElementWiseUnary){
    MatrixNxM mat(100,100);
    assignMatrixFunction(mat,[](int i,int j)->double{return (i-50)*(j-50);});
    elementWiseSignumInPlace(mat);
  }
  TEST(3, OperationMatrixElementWiseUnary){
    matrix2::StaticMatrix<double,10,10> mat;
    assignMatrixFunction(mat,[](int i,int j)->double{return (i-5)*(j-5);});
    elementWiseSignumInPlace(mat);

  }

  TEST(4,MatrixElementWiseUnaryRuntimeOperation){
    matrix2::StaticMatrix<double,10,10> mat;
    assignMatrixFunction(mat,[](int i, int j)->double{return (i-5)*(j-5);});
    elementWiseUnaryInPlace(mat,[](double d)->double{return d*2;});
    
  }


  
  TEST(1, OperationMatrixCoefficientAccess){
    double a[3]={4,5,6};
    auto a1 = coefficient(a,0,0);
    auto a2 = coefficient(a,1,0);
    auto a3 = coefficient(a,2,0);

    double d;
    auto sameType = isSameType(a1,d);

    CHECK(a1==4);
    CHECK(a2==5);
    CHECK(a3==6);


  }
  TEST(2, OperationMatrixCoefficientAccess){
    double a[3]={4,5,6};
    const auto & constA = a;

    auto a1 = coefficient(constA,0,0);
    auto a2 = coefficient(constA,1,0);
    auto a3 = coefficient(constA,2,0);

    double d;
    auto sameType = isSameType(a1,d);

    CHECK(a1==4);
    CHECK(a2==5);
    CHECK(a3==6);


  }
  
  TEST(1, CrossProduct){
    double a[3]={1,0,0};
    Vector3D b(0,1,0);
    {
    auto c = cross(a,b);
    CHECK(c(0)==0);
    CHECK(c(1)==0);
    CHECK(c(2)==1);
    }
    {
    auto c=cross(b,a);
    CHECK(c(0)==0);
    CHECK(c(1)==0);
    CHECK(c(2)==-1);
    }    
  }

  TEST(1,innerProduct){
    double a[3]={2,3,1};
    Vector3D b(1,2,3);

    {
      auto c = dot(a,b);
      auto type = isSameType(c,double(0));
      CHECK(type);
      CHECK(c==11);
    }
  }

  TEST(1,MatrixCoefficientType){
    Matrix2x2 matA[2][2];
    auto a= isSameType<coefficientTypeOfInstance(matA), Matrix2x2>();   
    CHECK(a);
  }

  
  TEST(2,MatrixElementWiseMultiply){
    matrix2::StaticMatrix<Matrix2x2,2,2> matA,matB;
    matA(0,0)=Matrix2x2::Identity();
    matA(0,1)=Matrix2x2::Identity();
    matA(1,0)=Matrix2x2::Identity();
    matA(1,1)=Matrix2x2::Identity();
    matB(0,0)=Matrix2x2::Identity();
    matB(0,1)=Matrix2x2::Zero();
    matB(1,0)=Matrix2x2::Zero();
    matB(1,1)=Matrix2x2::Identity();

    auto result = multiply(matA,matB);
    auto sameType = isSameType(result,matA);
    CHECK(sameType);
    
    for(int i=0; i < 2;i++)for(int j=0; j < 2; j++)for(int k=0;k < 2; k++)for(int l=0; l< 2;l++){
      bool r=false;
      auto val = result(i,j)(k,l);
      if(i==j&&k==l)r=val==1;
      else r = val==0;
      CHECK(r);
    }
    
  }


  TEST(1,MatrixElementWiseMultiply){
    double a=4;
    double b = 0.5;
    auto result  =multiply(a,b);
    auto sameType=isSameType(a,result);
    CHECK(sameType);
    CHECK(result==2.0);
  }

  TEST(MatrixTraitIsScalar1, Traits){
    CHECK(isScalarMatrix(2));
    CHECK(isScalarMatrix<double>());
  }
  TEST(MatrixTraitIsScalar2, Traits){
    Matrix3x3 mat;
    CHECK(!isScalarMatrix(mat));
    CHECK(!isScalarMatrix<Matrix3x3>());

  }
  
  TEST(RowTraits, MatrixTraits){
    double d;
    CHECK(rowTraits(d)==Fixed);
    CHECK(rowTraits<int>()==Fixed);
  }
  TEST(RowTraits2,MatrixTraits){
    matrix2::DynamicMatrix<double> mat;
    CHECK(rowTraits(mat)==Dynamic);
    CHECK(rowTraits<matrix2::DynamicMatrix<double> >()==Dynamic);
  }
  TEST(RowTraits3,MatrixTraits){
    matrix2::StaticMatrix<double,1,1> mat;
    CHECK(rowTraits(mat)==Fixed);
    auto traits = rowTraits<matrix2::StaticMatrix<double,1,1> >();
    CHECK(traits==Fixed);
  }
  TEST(RowTraits4,MatrixTraits){
    std::function<double(int,int)> foo=[](int i, int j){return i==j?1.0:0.0;};
    CHECK(rowTraits(foo)==Infinite);
    CHECK(rowTraits<std::function<double(int,int)> >()==Infinite);
  }



  TEST(ColTraits, MatrixTraits){
    double d;
    CHECK(columnTraits(d)==Fixed);
    CHECK(columnTraits<int>()==Fixed);
  }
  TEST(ColTraits2,MatrixTraits){
    matrix2::DynamicMatrix<double> mat;
    CHECK(columnTraits(mat)==Dynamic);
    CHECK(columnTraits<matrix2::DynamicMatrix<double> >()==Dynamic);
  }


  
  TEST(ColTraits3,MatrixTraits){
    matrix2::StaticMatrix<double,1,1> mat;
    CHECK(columnTraits(mat)==Fixed);
    auto traits = columnTraits<matrix2::StaticMatrix<double,1,1> >();
    CHECK(traits==Fixed);
  }
  TEST(ColTraits4,MatrixTraits){
    std::function<double(int,int)> foo=[](int i, int j){return i==j?1.0:0.0;};
    CHECK(columnTraits(foo)==Infinite);
    CHECK(columnTraits<std::function<double(int,int)> >()==Infinite);
  }



  TEST(MatrixAssign2, Func){
    Vector3D vec;
    assignMatrixFunction(vec,[](int i, int j){return  3.0-i;});
    for(int i=0; i < 3; i++){
      CHECK(3-i==vec(i));
    }
  }

  TEST(MatrixAssign, Func){
    MatrixNxM matrix(4,4);    
    assignMatrixBlindly(matrix,std::function<double(size_t,size_t)>([](size_t i, size_t j){return i==j?1.0:0.0;}));
    for(int i=0; i < 4; i++){
      for(int j=0; j < 4;j++){
        if(i==j){
          CHECK(matrix(i,j)==1.0);
        }else{
          CHECK(matrix(i,j)==0.0);
        }
      }
    }
  }

  TEST(MatrixResize4, staticMatrix){
    Matrix3x3 mat;
    CHECK(resize(mat,3,3));
  }

  TEST(MatrixResize3, dynamicMatrix){
    MatrixNxM matrix(3,3);
    bool result = resize(matrix,5,5);
    CHECK(result);
    CHECK(matrix.rows()==5 && matrix.cols()==5);
  }
  
  TEST(MatrixResize1,double){
    double d =32;
    CHECK(!resize(d,2,2))
  }
  TEST(MatrixResize2,double){
    double d =32;
    CHECK(resize(d,1,1))
  }

  TEST(MatrixCoefficientType,double){
    // only compilation matters
    double d = coefficientTypeOfType(double)(0.0);
     d = coefficientTypeOfInstance(d)(0.0);
    CHECK(true);
  }
  TEST(MatrixCoefficientType,int){
    // only compilation matters
    int d = coefficientTypeOfType(int)(0.0);
    d = coefficientTypeOfInstance(d)(0.0);
    CHECK(true);
  }


  TEST(MatrixCoefficientAccess,double){
    double matrix = 5.0;
    auto coeff = coefficient(matrix,0,0);
    CHECK(coeff==5.0);
  }


TEST(MatrixCoefficientAccess1,doubleArr){
  double matrix[3][3] = {{1.0,2.0,3.0},{1.0,2.0,3.0},{1.0,5.0,3.0}};
  auto & coeff = coefficient(matrix,2,1);
  coeff = 2.3;
  CHECK(matrix[2][1]==2.3);
}
TEST(MatrixCoefficientAccess2,doubleArr){
  double matrix[3][2] = {{1.0,2.0},{1.0,2.0},{1.0,5.0}};
  auto & coeff = coefficient(matrix,1,1);
  coeff = 2.3;
  CHECK(matrix[1][1]==2.3);
}
TEST(MatrixCoefficientAccess2,doubleArr1d){
  double matrix[3]={1.0,5.0,3.0};
  auto & coeff = coefficient(matrix,1,0);
  CHECK(coeff==5.0);
  coeff = 2.3;
  CHECK(matrix[1]==2.3);
}

template<typename BinaryFunction>
class MatrixFunction{
  size_t _rows;
  size_t _cols;
  BinaryFunction  _function;
 
public:

  ~MatrixFunction(){
    
  }
  inline auto operator()(size_t i, size_t j)-> decltype(MatrixFunction<BinaryFunction>::_function(i,j))&&{
    return std::move(_function(i,j));
  }
  inline auto operator()(size_t i, size_t j)const->const decltype(MatrixFunction<BinaryFunction>::_function(i,j))&&{
    return std::move(_function(i,j));
  }
  MatrixFunction(size_t rows, size_t cols, BinaryFunction   function):_rows(rows),_cols(cols),_function(function){

  }
  inline size_t rows()const{return _rows;}
  inline size_t cols()const{return _cols;}
};
// todo... double is wrong
template<typename BinaryFunction> SpecializeMatrixCoefficientType(MatrixFunction<BinaryFunction>, double);

template<typename BinaryFunction>
auto lazyMatrix(size_t rows, size_t cols, BinaryFunction f)->MatrixFunction<BinaryFunction>{
  return MatrixFunction<BinaryFunction>(rows, cols,f);
}


TEST(MatrixCoefficientAccess1, StandardMatrix){
  matrix2::StaticMatrix<double,5,2> mat;
  auto & coeff = coefficient(mat,3,1);
  coeff = 22;
  CHECK(mat(3,1)==22);
}

TEST(MatrixAssign, FuncMatrix){
  matrix2::StaticMatrix<double,3,3> mat;
  bool result = assignMatrix(mat,lazyMatrix(3,3,[](int i, int j)->double{return i==j?1.0:0.0;}));
  CHECK(result);
  for(int i=0; i < mat.rows(); i++){
    for(int j=0; j < mat.cols();j++){
      if(i==j) {
        CHECK(mat(i,j)==1.0);
      }else{
        CHECK(mat(i,j)==0.0);
      }
    }
  }
}



TEST(rowcolcount1, scalar){
  double d = 23;
  CHECK(rows(d)==1);
  CHECK(cols(d)==1);
}


#define BINARYOP_TEST(NAME, OP, TYPE_A, TYPE_B, TYPE_C, STRING_A, STRING_B, STRING_C)\
  TEST(NAME##OP##TYPE_A##_##TYPE_B##_##TYPE_C,BinaryOperation){\
  typedef nspace::TYPE_A TypeA;\
  typedef nspace::TYPE_B TypeB;\
  typedef nspace::TYPE_C TypeC;\
  \
  TypeA a;\
  TypeB b;\
  TypeC cExpected;\
  TypeC cActual;\
  \
  nspace::deserializeString(a,STRING_A);\
  nspace::deserializeString(b,STRING_B);\
  nspace::deserializeString(cExpected,STRING_C);\
  \
  OP<TypeC,TypeA,TypeB>::operation(cActual,a,b);\
  bool result =nspace::math::shorthands::matrix::matricesEqual(cExpected,cActual, Real(0.0001));\
  CHECK(result);\
};


template<typename Operation>
class OperationTest : public virtual Log{
public:
  virtual bool execute()=0;
};


class UnitTest : 
  public virtual Log, 
  public virtual Task
{
  REFLECTABLE_OBJECT(UnitTest);
  SUBCLASSOF(Log);

  PROPERTY(bool, Result){}
  ACTION(ExecuteTest){runTask();}

protected:
  void runTask(){
    setResult(runTest());
  }
  virtual bool runTest()=0;
};



#define MATRIX_EQUALS_TEST(NAME,TYPE_A,TYPE_B,STRING_A,STRING_B,EPS,RESULT)\
  TEST(NAME##equals##TYPE_A##TYPE_B, MatrixComparison){\
  typedef TYPE_A TypeA;\
  typedef TYPE_B TypeB;\
  typedef Real ElementType;\
  bool actualResult =false;\
  TypeA a;\
  TypeB b;\
  deserializeString(a,STRING_A);\
  deserializeString(b,STRING_B);\
  ElementType epsilon=EPS;\
  bool expectedResult = RESULT;\
  OperationMatrixEquals<TypeA,TypeB,ElementType>::operation(actualResult,a,b,epsilon);\
  CHECK(actualResult==expectedResult);\
};

MATRIX_EQUALS_TEST(eq1,Vector3D,Vector3D,"1 2 3","1 2 3",0.001,true);
MATRIX_EQUALS_TEST(eq2,Vector3D,Vector3D,"1 2 3","1.0001 2.0001 3.0001",0.001,true);
MATRIX_EQUALS_TEST(eq3,Vector3D,Vector3D,"1 2 3","1.0001 2.0001 3.001001",0.001,false);

BINARYOP_TEST(add1,MatrixAddition,Vector3D,Vector3D,Vector3D,"1 2 3", "4 5 6", "5 7 9");
BINARYOP_TEST(add2,MatrixAddition,Vector3D,Vector3D,Vector3D,"0 0 0", "0 0 0", "0 0 0");
BINARYOP_TEST(add3,MatrixAddition,Vector3D,Vector3D,Vector3D,"0 0 1", "0 2 0", "0 2 1");

BINARYOP_TEST(add1,MatrixAddition,Matrix3x3,Matrix3x3,Matrix3x3,
  "1 0 0 0 1 0 0 0 1",
  "2 2 2 2 2 2 2 2 2",
  "3 2 2 2 3 2 2 2 3");

BINARYOP_TEST(add2,MatrixAddition,Matrix3x3,Matrix3x3,Matrix3x3,
  "0 0 0 0 0 0 0 0 0",
  "2 2 2 2 2 2 2 2 2",
  "2 2 2 2 2 2 2 2 2");

}
