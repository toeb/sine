#include <core.testing.h>
#include <math.matrix/core.h>


#include <math.integration.h>

using namespace nspace::math::integration;



TEST(1,time_step_type){
  TEST_DESCRIPTION(gets the second type of a integrable function which is the time step type)
    auto f = [](Real x,std::string b){};
  CHECK_TYPES(step_size_type<decltype(f)>::type,std::string);  
}
TEST(2,time_step_type){
  setTestDescription("gets the timestep type of a integrable function - if the function has only one argument it defaults to coefficient type of function's return value");
  auto f = [](Real x){};
  CHECK_TYPES(step_size_type<decltype(f)>::type,Real);  
}

TEST(1,time_type){
  setTestDescription("get the time type of an integrable function (argument 3)");
  auto f = [](Real x, Real h, std::string t){};
  CHECK_TYPES(time_type<decltype(f)>::type, std::string);

}

TEST(2,time_type){
  setTestDescription("get the time type of an integrable function (argument 3 or coefficient type of functions return value)");
  auto f = [](Real x, Real h){};
  CHECK_TYPES(time_type<decltype(f)>::type, Real);

}


TTEST(integrable_function_traitsCall, StateType){  
  auto f = [](StateType x){return x;};
  typedef integrable_function_traits<decltype(f)> traits;
  StateType x;
  nspace::matrixSetRandom(x);
  auto x1 = traits::call(f,x,0.1,0,0);

  CHECK_EQUAL(x,x1);
}

TTEST_INSTANCE(integrable_function_traitsCall, nspace::Vector3D);
TTEST_INSTANCE(integrable_function_traitsCall, double);
TTEST_INSTANCE(integrable_function_traitsCall, float);
TTEST_INSTANCE(integrable_function_traitsCall, nspace::Matrix3x3);
TTEST_INSTANCE(integrable_function_traitsCall, double[4]);





TEST(1,IStepper){
  setTestDescription("checks if IStepper correctly increments step count and call virtual doStep method");
  struct TestIStepper : public IStepper{
    std::string called;
    void doStep(){
      called="was called";
    }
  }uut;
  IStepper & stepper = uut;
  CHECK_EQUAL(0,stepper.i());
  stepper.step();
  CHECK_EQUAL(1,stepper.i());
  CHECK(uut.called=="was called");

}

template<typename F>
struct TestStepper :public Stepper<F>{
  TestStepper(F f):Stepper<F>(f){}
  void doStep(){
  }
};



TEST(0,Stepper){
  setTestDescription("Checks if Stepper is initialized correctly");
  auto f = [](Real x, Real h, Real t, int step){return x;};
  TestStepper<decltype(f)> uut(f);

  CHECK_EQUAL(0.0, uut.x());
  CHECK_EQUAL(0.0, uut.x0());
  CHECK_EQUAL(0.0, uut.t0());
  CHECK_EQUAL(0.0, uut.t());
  CHECK_EQUAL(0.02, uut.h0());
  CHECK_EQUAL(0.02, uut.h());

}
TEST(1,Stepper){
  setTestDescription("Checks if Stepper correctly advances time");  
  auto f = [](Real x, Real h, Real t, int step){return x;};
  TestStepper<decltype(f)> uut(f);
  uut.step();
  CHECK_EQUAL(0.0,uut.x0());
  CHECK_EQUAL(0.0,uut.x());
  CHECK_EQUAL(0.02, uut.t());
  CHECK_EQUAL(0.0,uut.t0());
}

TTEST(StepperFunctionCall,StateType){
  auto f=[](StateType x){return x;};  
  typedef integrable_function_traits<decltype(f)> traits;
  typename traits::TimeStepType h;
  typename traits::TimeType t;
  typename traits::StateType x;
  
  nspace::elementWiseSetConstant(h,0.01);
  nspace::elementWiseSetConstant(t,0.0);
  nspace::elementWiseSetConstant(x,1.5);
  TestStepper<decltype(f)> uut(f);
  auto result = uut.f(x,h,t);
  //CHECK_TYPES(typename decltype(result), typename std::decay<StateType>::type);
  CHECK_EQUAL(x,result);
}

TTEST_INSTANCE(StepperFunctionCall,double);
TTEST_INSTANCE(StepperFunctionCall,float);
TTEST_INSTANCE(StepperFunctionCall,int);
TTEST_INSTANCE(StepperFunctionCall,nspace::Vector3D);
TTEST_INSTANCE(StepperFunctionCall,nspace::Matrix3x3);
TTEST_INSTANCE(StepperFunctionCall,double[4]);
TTEST_INSTANCE(StepperFunctionCall,float[4]);


//TTEST_INSTANCE(StepperFunctionCall,double[4][4]); does not work  cannot convert parameter 2 from 'double' to 'const double (&)[4]'




TEST(1,ExplicitEuler){
  auto f=[](Real x, Real h, Real t, int i)->Real{return t;};
  ExplicitEuler<decltype(f)> uut(f);
  uut.h()=0.001;
  uut.stepUntil(1.0);

  logInfo("error: "<< abs(uut.x()-0.5));
  DOUBLES_EQUAL(0.5,uut.x(), 0.001);
}

PTEST(PerformanceExplicitEuler){
  static auto f=[](Real x, Real h, Real t, int i)->Real{return t;};
  static auto uut = ExplicitEuler<decltype(f)>(f);
  static auto temp=[](){uut.h()=0.001;  return true;}();
  uut();
}
PTEST(PreformanceExplicitEulerManual){
   static auto f=[](Real x, Real h, Real t, int i)->Real{return t;};
   static Real x=0.0;
   static int i=0; 
   static Real t=0;
   static Real h=0.001;
 
   t=t+h;
   i++;
   x=x+f(x,h,t,i)*h;

}

PTEST(PerformanceImplicitEuler){
  static auto f=[](Real x, Real h, Real t, int i)->Real{return t;};
  static auto uut = ImplicitEuler<decltype(f)>(f);
  static auto temp=[](){uut.h()=0.001;  return true;}();

  uut();
}


TEST(2,ExplicitEuler){
  auto f=[](Real x, Real h, Real t, int i)->Real{return nspace::scalar::sine(t);};
  ExplicitEuler<decltype(f)> uut(f);
  uut.h()=0.001;
  uut.stepUntil(nspace::scalar::pi<Real>());

  auto analyticalResult = 2.0; // integral from t=0 to Pi over sin(t) = -cos(Pi)+cos(0) = 1+1=2

  logInfo("error: "<< abs(uut.x()-analyticalResult));
  DOUBLES_EQUAL(analyticalResult,uut.x(), 0.001);
}

/*
TEST(3,ExplicitEuler){
  using namespace nspace;
  auto f=[](Vector3D x, Real h, Real t){
    return Vector3D::UnitX()*t+Vector3D::UnitY()*scalar::sine(scalar::pi<Real>())+Vector3D::UnitZ()*x(2); 
  };
  auto uut = ExplicitEuler<decltype(f)>(f);
  uut.h()=0.001;
  uut();

  CHECK(uut.i()==1);
  

}
*/

TEST(1,ImplicitEuler){
  auto f=[](Real x, Real h, Real t, int i)->Real{return t;};
  ImplicitEuler<decltype(f)> uut(f);
  uut.h()=0.001;
  uut.stepUntil(1.0);

  logInfo("error: "<< abs(uut.x()-0.5));
  DOUBLES_EQUAL(0.5,uut.x(), 0.001);
}



TEST(2,ImplicitEuler){
  auto f=[](Real x, Real h, Real t, int i)->Real{return nspace::scalar::sine(t);};
  ImplicitEuler<decltype(f)> uut(f);
  uut.h()=0.001;
  uut.stepUntil(nspace::scalar::pi<Real>());

  auto analyticalResult = 2.0; // integral from t=0 to Pi over sin(t) = -cos(Pi)+cos(0) = 1+1=2

  logInfo("error: "<< abs(uut.x()-analyticalResult));
  DOUBLES_EQUAL(analyticalResult,uut.x(), 0.001);
}












