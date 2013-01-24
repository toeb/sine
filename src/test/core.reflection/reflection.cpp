#include <core.testing.h>



TEST(Toeb){
  std::cout  << "lol"<<std::endl;
  DS_UNIT_TEST_CHECK(false);
}

TEST(Toeb2){
  DOUBLES_EQUAL(1.1,1.2,0.05);
}