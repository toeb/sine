#include <CppUnitLite/TestHarness.h>
#include <string>
#include <math.matrix/types.h>
#include <core.logging.h>
#include <core.task.h>
#include <core/Serialization.h>
namespace nspace{

  

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
  inline auto operator()(size_t i, size_t j)->typename decltype(_function(i,j))&&{
    return std::move(_function(i,j));
  }
  inline auto operator()(size_t i, size_t j)const->const typename decltype(_function(i,j))&&{
    return std::move(_function(i,j));
  }
  MatrixFunction(size_t rows, size_t cols, BinaryFunction   function):_rows(rows),_cols(cols),_function(function){

  }
  inline size_t rows()const{return _rows;}
  inline size_t cols()const{return _cols;}
};

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