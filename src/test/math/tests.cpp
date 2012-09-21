#include <CppUnitLite/TestHarness.h>
#include <string>

#include <math.linearalgebra/types.h>

#include <math/ScalarOperations.h>



using namespace nspace;
using namespace nspace::math;
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


TEST(Signum,ScalarOperations){
  CHECK_EQUAL(-1.0,scalar::signum(-3.0));
  CHECK_EQUAL(1.0,scalar::signum(+93.0));
  CHECK_EQUAL(1.0,scalar::signum(0.0));
}


TEST(Cosine,ScalarOperations){
  DOUBLES_EQUAL(1.0,scalar::cosine(0.0),EPSILON);
  DOUBLES_EQUAL(-1.0,scalar::cosine(M_PI),EPSILON);
  DOUBLES_EQUAL(0,scalar::cosine(M_PI_2),EPSILON);
}

TEST(Absolute,ScalarOperations){
  DOUBLES_EQUAL(4.0,scalar::absolute(-4.0),EPSILON);
  DOUBLES_EQUAL(4.0,scalar::absolute(4.0),EPSILON);
}

TEST(ArcusSinus,ScalarOperations){
  DOUBLES_EQUAL(-M_PI_2,scalar::arcusSinus(-1.0),EPSILON);
  DOUBLES_EQUAL(M_PI_2,scalar::arcusSinus(1.0),EPSILON);
  DOUBLES_EQUAL(0,scalar::arcusSinus(0.0),EPSILON);
}
