#include <core.property.h>
#include <core.reflection.h>

struct A{
  REFLECTABLE_OBJECT(A);

  ACTION(Hallo){
    std::cout << "huhu"<<std::endl;
  }


  
};

int main(){
  A a;
  auto sa =a.getMethodInfo("Hallo");
  sa->call(&a);
  return 0;
}
