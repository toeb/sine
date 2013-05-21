/**
 * \file  src\test\test.core.testing\tests.cpp
 *
 * \brief Implements the tests class.
 */

#include <core.testing.h>

UNITTEST(Test1){
  // a test which checks a bool condition
  CHECK(true);

}
UNITTEST(Test2){
  CHECK_EQUAL(4,4);
}
UNITTEST(Test3){
  DOUBLES_EQUAL(3.9,4.0,0.2);
}


int main(){

  return nspace::UnitTestRunner::runCommandLine();

}