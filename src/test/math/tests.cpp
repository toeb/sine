#include <CppUnitLite/TestHarness.h>
#include <string>

#include <math.linearalgebra/types.h>



using namespace nspace;

TEST(IdentityCreation, Quaternion){
  Quaternion q = Quaternion::Identity();
  
  CHECK_EQUAL(1.0,q(0));
  CHECK_EQUAL(0.0,q(1));
  CHECK_EQUAL(0.0,q(2));
  CHECK_EQUAL(0.0,q(3));

  CHECK_EQUAL(1.0,q.w());
  CHECK_EQUAL(0.0,q.x());
  CHECK_EQUAL(0.0,q.y());
  CHECK_EQUAL(0.0,q.z());
}


