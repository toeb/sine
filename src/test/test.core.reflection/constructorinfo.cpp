#include <core.testing.h>
#include <core.reflection.h>
struct A{
  reflect_type(A);
public:
  reflected_constructor(public: A, int i, int j, int k){
    sum = i+j+k;
  }
  int sum ;
}a(1,2,3);


UNITTEST(CallConstructor1){
  auto type = typeof(A);
  auto constructor = type->Constructors().first();
  int args[3] = {1,2,3};
  auto instance= constructor->call(args);
  auto theA= (A*)instance;
  CHECK_EQUAL(6,theA->sum);
}

UNITTEST(CallableConstructor){
  auto type = typeof(A);
  auto constructor = type->Constructors().first();
  int args[3]={4,4,4};
  auto instance = (A*)(*constructor)(args);
  CHECK_EQUAL(12,instance->sum);
}

