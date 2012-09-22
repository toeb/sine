#include "RungeKuttaFehlberg45.h"
using namespace nspace;
using namespace std;
// coefficients needed for rkf45
#define c20 1.0/4.0
#define c21 1.0/4.0
#define c30 3.0/8.0
#define c31 3.0/32.0
#define c32 9.0/32.0
#define c40 12.0/13.0
#define c41 1932.0/2197.0
#define c42 -7200.0/2197.0
#define c43 7296.0/2197.0
#define c50 1.0
#define c51 439.0/216.0
#define c52 -8.0
#define c53 3680.0/513
#define c54 -845.0/4104.0
#define c60 1.0/2.0
#define c61 -8.0/27.0
#define c62 2.0
#define c63 -3544.0/2565.0
#define c64 1859.0/4104.0
#define c65 -11.0/40.0
#define z1 16.0/135.0 
#define z2 6656.0/12825.0 
#define z3 28561.0/56430.0
#define z4 -9.0/50.0
#define z5 2.0/55.0
#define y1 25.0/216.0
#define y2 1408.0/2565.0
#define y3 2197.0/4101.0
#define y4 -1.0/5.0


RungeKuttaFehlberg45::RungeKuttaFehlberg45(
  Real tolerance, 
  Real h0, 
  Real alpha,
  Real beta,
  Real gamma,
  Real maxStepSize,
  Real minStepSize
  ):StepIntegrator(h0)
    , alpha(alpha)
    , beta(beta)
    , gamma(gamma)
    , tolerance(tolerance)
    , maximumStepSize(maxStepSize)
    , minimumStepSize(minStepSize)
    { setName("RungeKuttaFehlberg45"); };

/**
  * \brief Sets a tolerance.
  *
  * \param tolerance The tolerance.
  */
void RungeKuttaFehlberg45::setTolerance(const Real tolerance){
  this->tolerance = tolerance;
}

/**
  * \brief Gets the tolerance.
  *
  * \return  The tolerance.
  */
Real RungeKuttaFehlberg45::getTolerance(){
  return tolerance;
}

/**
  * \brief Gets the error order. which is 5 in case of the rkf45 algorithm
  *
  * \return  The error order.
  */
int RungeKuttaFehlberg45::getErrorOrder()const{
  return 6;
}

const Real& RungeKuttaFehlberg45::getErrorEstimate()const{
  return currentErrorEstimate;
}
  
void RungeKuttaFehlberg45::logParameters(std::ostream & o)const{
 // StepIntegrator::logParameters(o);
  o<<"<parameter name=\"tolerance\">"<<tolerance<<"</parameter>\n";
  o<<"<parameter name=\"alpha\">"<<alpha<<"</parameter>\n";
  o<<"<parameter name=\"beta\">"<<beta<<"</parameter>\n";
  o<<"<parameter name=\"gamma\">"<<gamma<<"</parameter>\n";
  o<<"<parameter name=\"maximumStepSize\">"<<maximumStepSize<<"</parameter>\n";
  o<<"<parameter name=\"minimumStepSize\">"<<minimumStepSize<<"</parameter>\n";
}

void RungeKuttaFehlberg45::calculateRungeKutta45(Real t_i, const StateMatrix & x_i, Real h, StateMatrix & rk4, StateMatrix & rk5){
  // calculate k values
  k1 = h * f(x_i,                                                      t_i,           h);
  k2 = h * f(x_i+c21*k1 ,                                          c20*t_i,           h);
  k3 = h * f(x_i+c31*k1 + c32 * k2,                                c30*t_i,           h);
  k4 = h * f(x_i+c41*k1 + c42 * k2+c43 * k3,                       c40*t_i,           h);
  k5 = h * f(x_i+c51*k1 + c52 * k2+c53 * k3 + c54 * k4,            c50*t_i,           h);
  k6 = h * f(x_i+c61*k1 + c62 * k2+c63 * k3 + c64 * k4 + c65 * k5, c60*t_i,           h);
  //calculate the 4th order approximation
  y = x_i + y1 * k1 + y2*k3 + y3*k4 +y4*k5;
  //calculate the 5th order approximation
  z = x_i + z1 * k1 + z2* k3 + z3*k4 +z4*k5+z5*k6;
}
/**
  * \brief Steps th integrator by h seconds.  uses the RKF45 algorithm.
  *
  * \param t_i The time t_i.
  * \param h   The timestep h.
  *
  * \return  the approximate value.
  */
void RungeKuttaFehlberg45::doStep(StateMatrix & x_next, const StateMatrix & x, Real t_i, Real h_i){
  //calculates runge kutta of order 4 and 5 at state x_i
  calculateRungeKutta45(t_i,x,h_i,y,z);
  // calculate the error estimate 
  currentErrorEstimate =  (y-z).norm();
  Real s =  pow(tolerance*h_i/currentErrorEstimate,1.0/4.0); 
  Real h_star = s * h_i;
  Real h_new =h_star*alpha; // h star * alpha reduces the step size causing overhead but since f is changing the overall efficiency is increased
  // stepsize increase is bounded by h*beta
  if(h_new>beta*h_i)h_new =  beta  * h_i;
  //stepsize decrease is bounded by h*gamma
  if(h_new<gamma*h_i)h_new = gamma * h_i;
  //general stepsize constraining can be done here.
  if(minimumStepSize > h_new)h_new = minimumStepSize;
  if(maximumStepSize < h_new)h_new = maximumStepSize;
    
  h() = h_new;

  //if(getNumberOfSteps()%10==0)cout << h_new<<" "<< currentErrorEstimate<<endl;
  //return the higher order approximation
  x_next = z;
}
