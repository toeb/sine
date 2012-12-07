#include <CppUnitLite/TestHarness.h>
#include <string>
#include <math.matrix/types.h>

#include <core/Serialization.h>
namespace nspace{

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