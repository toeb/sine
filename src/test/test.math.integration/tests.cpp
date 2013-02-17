#include <core.testing.h>
#include <math.matrix/core.h>

#include <core/template/function_traits.h>


auto linearX = [](const Real x){return x;};
auto squaredX = [](const Real x){return x*x;};
auto zeroX = [](const Real x){return 0.0;};

struct Any{
  template<typename T2> operator T2();
};



/*
template<typename F, typename T1=Any, typename T2=Any, typename T3=Any, typename T4 = Any>
struct function_return_type{
typedef typename decltype(nspace::declval<F>()(T1(),T2(),T3(),T4())) type;
};
template<typename F, typename T1=Any, typename T2=Any, typename T3=Any>
struct function_return_type<F,T1,T2,T3,std::_Nil>{
typedef typename decltype(nspace::declval<F>()(T1(),T2(),T3())) type;
};
template<typename F, typename T1=Any, typename T2=Any>
struct function_return_type<F,T1,T2,std::_Nil,std::_Nil>{
typedef typename decltype(nspace::declval<F>()(T1(),T2())) type;
};

template<typename F, typename T1=Any>
struct function_return_type<F,T1,std::_Nil,std::_Nil,std::_Nil>{
typedef typename decltype(nspace::declval<F>()(T1())) type;
};*/


/*
*/


template<typename F, bool hasStepSize=nspace::function_traits<F>::arity==2||nspace::function_traits<F>::arity==3||nspace::function_traits<F>::arity==4 >
struct step_size_type{
  typedef typename nspace::coefficientTypeOfType(typename nspace::function_traits<F>::result_type) type;
};


template<typename F>
struct step_size_type<F,true>{
  typedef typename nspace::function_traits<F>::nested_template arg<1>::type type;

};

template<typename F, bool hasTime=nspace::function_traits<F>::arity==3||nspace::function_traits<F>::arity==4> 
struct time_type{
  typedef typename nspace::coefficientTypeOfType(typename nspace::function_traits<F>::result_type) type;
};
template<typename F>
struct time_type<F,true>{
  typedef typename nspace::function_traits<F>::nested_template arg<2>::type type;
};

template<typename F>
struct state_type{
  typedef typename nspace::function_traits<F>::result_type type;
};


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

struct IStepper{
  typedef size_t StepCount;
  StepCount _i;
  const StepCount & i()const{return _i;}
  void operator()(){step();}
  void operator()(const StepCount n){
    nSteps(n);
  }
  virtual void step(){    
    doStep();
    _i++;
  }
  void nSteps(const StepCount n){
    for(StepCount i =0; i < n; i++){
      step();
    }
  }  

  IStepper():_i(0){}
  virtual ~IStepper(){}
protected:
  virtual void doStep()=0;
};

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

//typename nspace::function_traits<F>::arg<0>::type
template<typename F, typename X=typename  state_type<F>::type, typename H =typename step_size_type<F>::type,typename T = typename  time_type<F>::type>
struct Stepper : public IStepper{
  typedef F FunctionType;
  typedef X StateType;
  typedef H TimeStepType;
  typedef T TimeType;
  typedef typename nspace::coefficientTypeOfType(X) CoefficientType;

  FunctionType _function;
  StateType _x0;
  StateType _x;
  TimeStepType _h0;
  TimeStepType _h;
  TimeType _t0;
  TimeType _t;


  const TimeType & t()const{return _t;}
  const TimeType & t0()const{return _t0;}
  const StateType & x()const {return _x;}
  StateType & x() {return _x;}
  const StateType & x0()const{return _x0;}
  const TimeStepType & h()const{return _h;}
  TimeStepType & h(){return _h;}
  const TimeStepType & h0()const{return _h0;}

  Stepper(FunctionType function, 
    StateType x0=0,
    TimeType t0=0,
    TimeStepType h0=0.02
    ):_x0(x0),_x(_x0), _h0(h0),_h(_h0),_t0(t0),_t(_t0){}
  virtual void step(){
    IStepper::step();    
    _t=_t+_h;
  }

  void stepUntil(const TimeType t_end){
    while(t()<=t_end){
      step();
    }
  }
  StateType f(StateType x, TimeStepType h, TimeType t){return _function(x,h,t,i());}
};

template<typename F>
struct TestStepper :public Stepper<F>{
  TestStepper(F f):Stepper(f){}
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




template<typename F, typename X=state_type<F>::type, typename H =step_size_type<F>::type,typename T = time_type<F>::type >
struct SingleStepSolver : public Stepper<F,X,H,T>{
  SingleStepSolver(FunctionType f):Stepper(f){}

};
struct MultiStepSolver{

};



template<typename F, typename X=nspace::function_traits<F>::result_type, typename H =step_size_type<F>::type, typename T = time_type<F>::type>
struct ExplicitEuler :public SingleStepSolver<F,X,H,T>{
  ExplicitEuler(F f):SingleStepSolver(f){}
  void doStep(){    
    x()=x()+h()*f(x(),h(),t());
  }
};

template<typename F, typename X=nspace::function_traits<F>::result_type, typename H =step_size_type<F>::type, typename T = time_type<F>::type>
struct ImplicitEuler :public SingleStepSolver<F,X,H,T>{
  ImplicitEuler(F f):SingleStepSolver(f),_maxIterations(100),_tolerance(0.001){}

  StepCount _maxIterations;
  CoefficientType _tolerance;

  void doStep(){    
    StateType tmp;
    CoefficientType diffSquared;
    //fix point iteration
    auto toleranceSquared = _tolerance*_tolerance;    
    size_t iteration=0;  
    while(iteration < _maxIterations){
      iteration++;
      tmp = x() + h() * f(x(),h(),t());
      diffSquared = nspace::lengthSquared(nspace::subtract(tmp,x()));
      x() = tmp;
      if(diffSquared < toleranceSquared)break;
    }
  }
};





template<typename Integrator,typename F>
Integrator make_integrator(F f){
  return Integrator<F>(f);
}

TEST(1,ExplicitEuler){
  auto f=[](Real x, Real h, Real t, int i)->Real{return t;};
  ExplicitEuler<decltype(f)> uut(f);
  uut.h()=0.001;
  uut.stepUntil(1.0);

  logInfo("error: "<< abs(uut.x()-0.5));
  DOUBLES_EQUAL(0.5,uut.x(), 0.001);
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

/*
struct SemiExplicitEuler{

};/*
struct ImplicitEuler: public SingleStepSolver {
void step(){
int i=0;
int maxIterations = 100;
double tolerance = 0.001;
double tmp;
double diff;
//fix point iteration

//x_next = x_i;
while(i < maxIterations){
i++;
tmp = x + h * f(x,h,t);
diff = abs(tmp -x);
x = tmp;
if(diff < tolerance)break;
}
}
};
UNITTEST(ExplicitEuler2){
/* auto f = [](Real x)->Real{return 0.0;};
ExplicitEuler<decltype(f)> uut(f);
uut.h = 0.01;

CHECK_EQUAL(0,uut.i);
CHECK_EQUAL(0.0,uut.x);
uut.doStep();
CHECK_EQUAL(1,uut.i);
CHECK_EQUAL(0.0,uut.x); */
//}
/*
TTEST(ZeroIntegration,Solver){

}*/
//TTEST_INSTANCE(ExplicitEuler, ImplicitEuler)