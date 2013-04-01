#include <core.testing.h>

#include <core.reflection.h>
#include <array>


using namespace nspace;
using namespace std;



TEST(3,CallableFunctor){
  auto it =make_callable([](string s)->int{return strtol(s.c_str(),0,10);});  
  auto res =  (int)it(string("32"));
  CHECK(res == 32);
}
  
TEST(2,CallableFunctor){
  struct A{
    A(){
      lastOpResult=0;
    }
    int lastOpResult;
    int operator ()(int i, int j, int k){
      return lastOpResult = i+j+k;
    }
  };
  CallableFunctor<A> cf; 
  Callable * c= &cf;
  auto result = (int)c->operator()(5,2,3);
  CHECK(10==result);
  c->operator()(1,1,1);
  CHECK(3==cf._function.lastOpResult);
}


TEST(1,CallableFunctor){
  struct A{
    int operator ()(int i, int j, int k)const{
      return i+j+k;
    }
  };
  CallableFunctor<A> cf; 
  Callable * c= &cf;
  auto result = (int)c->operator()(5,2,3);
  CHECK(10==result);
}


TEST(1,DS_CLASS){
  // tests weather typeof(A) correctly returns a type
  struct A{
    DS_CLASS(A);
  };
  auto type = typeof(A);
  CHECK(type!=0);
}
TEST(2,DS_CLASS){
  // tests the typeof(...) and getType operation 
  struct A{
    DS_CLASS(A);
  };
  A a;
  auto type = a.getType();
  CHECK(typeof(A)==type);
}
TEST(3,DS_CLASS){
  // this tests whether the Derived class correctly overrides 
  // the base classes getType() method
  struct Base{
    DS_CLASS(Base)
  }base;
  struct Derived : public Base{
    DS_CLASS(Derived)
  }derived;
  auto  baseType = base.getType();
  auto  derivedType = derived.getType();

  CHECK(baseType != derivedType);
}
TEST(4,DS_CLASS){
  // this tests whether the Derived class still functions when not parttaking in reflection
  // the base classes getType() method
  struct Base{
    DS_CLASS(Base)
  }base;

  struct HiddenDerived : public Base{

  }hidden;
  auto  baseType = base.getType();
  auto  derivedType = hidden.getType();

  CHECK_EQUAL(baseType , derivedType);
}



