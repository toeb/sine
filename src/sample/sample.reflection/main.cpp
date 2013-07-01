//#include <core.property.h>
#include <core.reflection.h>
#include <iostream>
#include <core/template/function_traits.h>
#include <functional>
#include <core.reflection/callable/TypedArgumentInfo.h>

template<typename T, typename ArgumentTuple=void>
struct ConstructorSignature{

};
template<typename T>
struct ConstructorSignature<T,void>{
  static T * constructRawPointer(){
    return new T();
  }
  static std::shared_ptr<T> constructSharedPointer(){
    return std::make_shared<T>();
  }  
  static T * constructInMemory(void * ptr){
    new (ptr) T ();
  }
};
template<typename T,typename T1>
struct ConstructorSignature<T,std::tuple<T1>>{
  static T * constructRawPointer(T1 a0){
    return new T(a0);
  }
  static std::shared_ptr<T> constructSharedPointer(T1 a0){
    return std::make_shared<T>(a0);
  }  
  static T * constructInMemory(void * ptr,T1 a0){
    new (ptr) T (a0);
  }
};
template<typename T,typename T1,typename T2>
struct ConstructorSignature<T,std::tuple<T1,T2>>{
  static T * constructRawPointer(T1 a0,T2 a1){
    return new T(a0,a1);
  }
  static std::shared_ptr<T> constructSharedPointer(T1 a0,T2 a1){
    return std::make_shared<T>(a0,a1);
  }  
  static T * constructInMemory(void * ptr,T1 a0,T2 a1){
    new (ptr) T (a0,a1);
  }
};




template<typename Callable>
struct TypedCallableInfo{

};
namespace nspace{
  template<typename TCallable>
  struct TypedCallableInfoBase : public nspace::CallableInfo{
    typedef TCallable callable_type;
    propdef callable_type basic_property(Callable);

  protected:
    TypedCallableInfoBase():CallableInfo(),_Callable(callable){

    }
  };
}

template<typename Class,typename ReturnValue>
struct TypedCallableInfo<ReturnValue (Class::*)()> 
  : public nspace::TypedCallableInfoBase<ReturnValue (Class::*)()>{
    TypedCallableInfo(callable_type callable) : TypedCallableInfoBase<callable_type>(callable){
      setIsConst(false); 
    }
};
template<typename Class,typename ReturnValue>
struct TypedCallableInfo<ReturnValue (Class::*)()const>
  : public nspace::TypedCallableInfoBase<ReturnValue (Class::*)()const>{
    TypedCallableInfo(callable_type callable) : TypedCallableInfoBase<callable_type>(callable){
      setIsConst(true); 
    }
};

template<typename Class,typename ReturnValue,typename T1>
struct TypedCallableInfo<ReturnValue (Class::*)(T1)> 
  :nspace::TypedCallableInfoBase<ReturnValue (Class::*)(T1)>{
  TypedCallableInfo(callable_type callable):TypedCallableInfoBase<callable_type>(callable){
    setIsConst(false);    
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1,0>>());
  }
};
template<typename Class,typename ReturnValue,typename T1>
struct TypedCallableInfo<ReturnValue (Class::*)(T1)const> 
  :nspace::TypedCallableInfoBase<ReturnValue (Class::*)(T1)const>{
  TypedCallableInfo(callable_type callable):TypedCallableInfoBase<callable_type>(callable){
    setIsConst(true);    
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1,0>>());
  }
};

template<typename Class,typename ReturnValue,typename T1,typename T2>
struct TypedCallableInfo<ReturnValue (Class::*)(T1,T2)> 
  :nspace::TypedCallableInfoBase<ReturnValue (Class::*)(T1,T2)>{
  TypedCallableInfo(callable_type callable):TypedCallableInfoBase<callable_type>(callable){
    setIsConst(false);    
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1,0>>());
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2,1>>());
  }
};
template<typename Class,typename ReturnValue,typename T1,typename T2>
struct TypedCallableInfo<ReturnValue (Class::*)(T1,T2)const>
  :nspace::TypedCallableInfoBase<ReturnValue (Class::*)(T1,T2)const>{
  TypedCallableInfo(callable_type callable):TypedCallableInfoBase<callable_type>(callable){
    setIsConst(true);    
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1,0>>());
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2,1>>());
  }
};

template<typename ReturnValue>
struct TypedCallableInfo<ReturnValue (*)()>
  :nspace::TypedCallableInfoBase<ReturnValue (*)()>{
   TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
    setIsConst(true);
  }
};
template<typename ReturnValue,typename T1>
struct TypedCallableInfo<ReturnValue (*)(T1)>
  :nspace::TypedCallableInfoBase<ReturnValue (*)(T1)>{
   TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
    setIsConst(true);    
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1,0>>());
  }
};
template<typename ReturnValue,typename T1,typename T2>
struct TypedCallableInfo<ReturnValue (*)(T1,T2)>
  :nspace::TypedCallableInfoBase<ReturnValue (*)(T1,T2)>{
  TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
    setIsConst(true);    
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1,0>>());
    Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2,1>>());
  }
};



struct TestClass{
  TestClass(int i, double j){

  };
  TestClass(int i, int j){

  };
  TestClass(int i){

  };
  TestClass(double j){

  };

  TestClass(){

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

template<typename T>
TypedCallableInfo<T> info(T info){
  return TypedCallableInfo<T>(info);
}
template<typename T>
TypedCallableInfo<std::shared_ptr<T> (*)()> info_constructor(){
  return info(&ConstructorSignature<T,void>::constructSharedPointer);
}
template<typename T,typename T1>
TypedCallableInfo<std::shared_ptr<T> (*)(T1)> info_constructor(){
  return info(&ConstructorSignature<T,std::tuple<T1>>::constructSharedPointer);
}
template<typename T,typename T1,typename T2>
TypedCallableInfo<std::shared_ptr<T> (*)(T1,T2)> info_constructor(){
  return info(&ConstructorSignature<T,std::tuple<T1,T2>>::constructSharedPointer);
}
int lol(){return 3;}


int main(){
  auto i1= info_constructor<TestClass>();
  auto i13= info_constructor<TestClass,int,int>();
  auto i14= info_constructor<TestClass,int,double>();
  auto i15= info_constructor<TestClass,int>();
  auto i16 = info_constructor<TestClass,double>();
  //auto i2 = info(fuu);
  auto i3 = info(&someMethod);
  auto i4 = info(nspace::signature<int,int>( &TestClass::add));
  auto i5 = info(nspace::const_signature<int,int>( &TestClass::add));
  auto i6 = info(nspace::const_signature<int,double>( &TestClass::add));
  auto i7 = info(&TestClass::mul2);
  auto i8 = info(&TestClass::mul3);
  auto i9 = info(nspace::static_signature( &TestClass::add));
  auto i11 = info(&TestClass::operator());


  //  auto i7 = info(nspace::signature<double,double>( &TestClass::add));



  return 0;
}
