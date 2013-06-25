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



UNITTEST(UnivasiveConstrucotrReflection){

}


UNITTEST(CallDefaultConstructor1){
 struct B{
   reflect_type(B);
 public:
   reflected_default_constructor(public :B){}
 }
 b;
 auto & type= *typeof(B)->Constructors().first();
 auto instance = type().cast<B>();
 CHECK((bool)instance);
}

UNITTEST(CallDefaultConstructor2){
 struct B{
   reflect_type(B);
 public:
   int val;
   reflected_default_constructor(public :B){
     val =3;
   }
 }
 b;
 auto & type= *typeof(B)->Constructors().first();
 auto instance = type().cast<B>();
 CHECK_EQUAL(3,instance->val);
}
UNITTEST(CallConstructor1){
  auto type = typeof(A);
  auto constructor = type->Constructors().first();
  int args[3] = {1,2,3};
  auto instance= constructor->call(args);
  auto theA= instance.cast<A>();
  CHECK((bool)instance);
  CHECK_EQUAL(6,theA->sum);
}

UNITTEST(CallableConstructor2){
  auto type = typeof(A);
  auto constructor = type->Constructors().first();
  int args[3]={4,4,4};
  auto instance = constructor->call(args).cast<A>();
  CHECK((bool)instance);
  CHECK_EQUAL(12,instance->sum);
}


UNITTEST(CallableConstructor3){
  auto type = typeof(A);
  auto &constructor = *type->Constructors().first();
  auto instance = constructor(9,3,9).cast<A>();
  CHECK((bool)instance);
  CHECK_EQUAL(21,instance->sum);
}


