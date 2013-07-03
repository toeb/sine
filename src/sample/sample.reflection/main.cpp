//#include <core.property.h>
#include <core.reflection.h>
#include <iostream>
#include <core/template/function_traits.h>
#include <functional>
#include <core.reflection/callable/TypedArgumentInfo.h>
#include <core.reflection/member/constructor/TypedConstructorInfo.h>




struct TestClass{
  int _i;
  int _j;
  TestClass(int i, double j):_i(i){

  };
  TestClass(int i, int j):_i(i),_j(j){

  };
  TestClass(int i){

  };
  TestClass(double j){

  };

  TestClass(){
    _i=22222;
    _j = 333;
  };
  double operator()(double i, double j){return i*j*i;}
  double mul2 (double a, double b){return a*b;}
  static double mul3(double a, double b){return a*b;}
  int add(int i, int j){return i+j;}
  int add(int i, int j)const{return i+j;}
  double add(int i, double j)const{return i+j;}
  static double add(double i, double j){return i+j;}
};
std::string someMethod(){
  return "mememe";
}
int mul(int i, int j){return i*j;}
double mul(int i, double j){return i*j;}

auto fuu = [](double d){return d+1;};

int lol(){return 3;}

void fuu2(){
}
template <typename T>
ArgumentFor(std::function<T()> f){
  f();
  return nspace::Argument();
}
int main(){
  using namespace nspace;
  ArgumentFor([](){return fuu2();});
  auto a  =typed_method_info(const_signature<int,double>(&TestClass::add));
  std::cout << std::endl;
  /*
   auto asdasd = type_of<int>();
  // std::shared_ptr<TestClass> (*b)(int&&,int&&) = &make<TestClass>::shared<int,int>;
  //auto a = &make<TestClass>::shared_2<int,int>;*/
/*  auto & type = *nspace::core::reflection::builder::reflect<TestClass>()
    ->constructor<int,int>()
    ->end()
    ->constructor<int,double>()
    ->end()
    ->constructor<int>()
    ->end()
    ->constructor<double>()
    ->end()
    ->constructor()
    ->end()
    ->method(const_signature<int,double>(&TestClass::add))
    ->end()
    ->method(signature<int,int>(&TestClass::add))
    ->end()
    ->end();

  /*
  auto & aaaa = core::reflection::registry();
  auto it =(std::shared_ptr<TestClass>)type(3,2.2);

  /*
    auto a1 =TypedConstructorInfo<TestClass,int,int>();
    
    std::shared_ptr<TestClass> b = a1(3,4);
    
    TestClass * b2 = (*a1.getMakeRaw())(3,4);

    TestClass* jsm=(TestClass*) malloc(sizeof(TestClass));
    (*a1.getMakePlacement())(jsm,44,22);
    */
    

    /*auto  s =a1(5,4).cast<TestClass>();
    TestClass wot =a1(3,4);
    auto s2 = s.get();

    auto a2 =TypedConstructorInfo<TestClass,int,double>();
    auto a3 =TypedConstructorInfo<TestClass,int>();
    auto a4 =TypedConstructorInfo<TestClass,double>();
    auto a5 =TypedConstructorInfo<TestClass>();

    /*
    auto i1= info_constructor_shared<TestClass>();
    auto i13= info_constructor_shared<TestClass,int,int>();
    auto i14= info_constructor_shared<TestClass,int,double>();
    auto i15= info_constructor_shared<TestClass,int>();
    auto i16 = info_constructor_shared<TestClass,double>();*/
    //auto i2 = info(fuu);
    /*
    auto i3 = callable_info(&someMethod);
    auto i4 = callable_info(nspace::signature<int,int>( &TestClass::add));
    auto i5 = callable_info(nspace::const_signature<int,int>( &TestClass::add));
    auto i6 = callable_info(nspace::const_signature<int,double>( &TestClass::add));
    auto i7 = callable_info(&TestClass::mul2);
    auto i8 = callable_info(&TestClass::mul3);
    auto i9 = callable_info(nspace::static_signature( &TestClass::add));
    auto i11 = callable_info(&TestClass::operator());*/


    //  auto i7 = info(nspace::signature<double,double>( &TestClass::add));



    return 0;
}
