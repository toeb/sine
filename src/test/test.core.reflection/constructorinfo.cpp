#include <core.testing.h>
#include <core.reflection.h>


UNITTEST(a){
  struct A{
    reflect_type(A);
  public:
    reflect_constructor(public: A, int i, int j, int k){
      sum = i+j+k;
    }
    int sum ;
  }a(1,2,3);
  
  
  auto type = typeof(A);

  auto constructor = type->Constructors().first();

  int args[3] = {1,2,3};
  auto instance=   constructor->call(args);

  auto theA= instance.cast<A>();

}

