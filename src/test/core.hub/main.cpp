#include <core.testing.h>

using namespace nspace;


int main(){
  auto & instance = *UnitTestRunner::instance();
  instance.run();
  std::cout<<instance;

}