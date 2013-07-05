//#include <core.property.h>
#include <core.reflection.h>
#include <iostream>
#include <core/template/function_traits.h>
#include <functional>
#include <core.reflection/callable/TypedArgumentInfo.h>
#include <core.reflection/member/constructor/TypedConstructorInfo.h>

#include <core/template/callable_traits.h>
#include <core/template/type_tuple.h>
#include <array>

struct TestClass{
  int _i;
  int _j;
  TestClass(int i, double j):_i(i){
    
    _i=i;
    _j = j;
  };
  ~TestClass(){}
  TestClass(int i, int j):_i(i),_j(j){

  };
  TestClass(int i){
    _i=_j=i;
  };
  TestClass(double j){

  };

  TestClass(){
    _i=22222;
    _j = 333;
  };
  int geti()const {return _i;}
  int addddd(double d){return 0;}
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
int fuu3(){
  return 323;
}




struct myFu{
  std::function<void(const nspace::Type*)> toType;
  myFu(std::function<void(const nspace::Type*)> f):toType(f){}
  template<typename T>
  void operator()(){
    toType(nspace::type_of<T>());
  }
};
int main(){

  using namespace nspace;

  Argument arg1 =2;
  Argument arg2 =3.2;
  Argument a1 = arg1;
  Argument a2 = arg2;

  
  const std::array<Argument,2> aaa={2,3.2};

 // double && a32 =aaa[1];// (Argument)aaa[1];
/*  auto me = &make<TestClass>::shared_2<int,double>;
  auto b = call_callable(me,aaa);
 auto shared  =nspace::make<TestClass>::shared_2((int&&)a1,(double&&)a2);*/
  /*
  auto bb= shared_callable_info(static_signature<int,int>(&mul));
  int rrr = (*bb)(3,4);
  auto cc = shared_callable_info((&TestClass::mul2));
  TestClass cccccc;
  double rrrr = (*cc)(&cccccc,2.34,111.2);
  
  auto dd= shared_callable_info(fuu);
  double rrrrr= (*dd)(2.3);
  std::array<Argument,1> arr ={3.2};

  typedef decltype(fuu) ttt;
  auto result =  callable_traits<ttt>::call(fuu,arr);
  auto a = callable_traits<ttt>::arguments::at<0>::type();

  auto result2 = call_callable(fuu,arr);
  double r2=result2;
  double r=result;
  //callable_traits<decltype(&fuu2)>::*/
  /*
  auto asdasd = type_of<int>();
  // std::shared_ptr<TestClass> (*b)(int&&,int&&) = &make<TestClass>::shared<int,int>;
  //auto a = &make<TestClass>::shared_2<int,int>;*/
  auto & type = *nspace::core::reflection::builder::reflect<TestClass>()
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
    ->method(&TestClass::geti)
    ->name("geti")
    ->end()
  ->end();

  auto arg = type(2);
  int asd = (*arg.type->getMethod("geti"))(arg.data.get());

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
