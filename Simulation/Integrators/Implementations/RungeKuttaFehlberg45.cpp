#include "RungeKuttaFehlberg45.h"


using namespace IBDS;
using namespace std;

void RungeKuttaFehlberg45::doStep(const Real & h, VectorND & x_i){
  // calculate k values
    VectorND k1 = h * f(x_i);
    VectorND k2 = h * f(x_i + c21*k1 );
    VectorND k3 = h * f(x_i + c31*k1 + c32*k2);
    VectorND k4 = h * f(x_i + c41*k1 + c42*k2 + c43*k3);
    VectorND k5 = h * f(x_i + c51*k1 + c52*k2 + c53*k3 + c54*k4);
    VectorND k6 = h * f(x_i + c61*k1 + c62*k2 + c63*k3 + c64*k4 + c65*k5);
    //calculate the 4th order approximation
    VectorND y =	x_i + y1*k1 + y2*k3 + y3*k4 +y4*k5;
    //calculate the 5th order approximation (which is the result of this step)
    x_i =			x_i + z1*k1 + z2*k3 + z3*k4 +z4*k5 + z5*k6;
    // calculate the next timestep 
    Real err =  (y-x_i).length();//calculate error estimate
    Real s =  pow(_tolerance*h/err,1.0/4.0); // calculate step size scaling factor
    Real h_star = s * h; // calculate potential next step size
    Real h_next = h_star *_alpha; // h star * alpha reduces the step size causing overhead but since f is changing the overall efficiency is increased
    // stepsize increase is bounded by h*beta
    if(h_next<_beta*h)h_next =  _beta  * h;
    //stepsize decrease is bounded by h*gamma
    if(h_next>_gamma*h)h_next = _gamma * h;
    //constrain step size to [_minimumStepSize, _maximumStepSize]
    if(_minimumStepSize > h_next)h_next = _minimumStepSize;
    if(_maximumStepSize < h_next)h_next = _maximumStepSize;
    // set the step size to h_next
    setStepSize(h_next);
}

RungeKuttaFehlberg45::RungeKuttaFehlberg45(
  Real tolerance              ,
  Real initialStepSize        ,
  Real alpha                  ,
  Real beta                   ,
  Real gamma                  ,
  Real maxStepSize            ,
  Real minStepSize            
  ):
  _tolerance(tolerance)
  ,_alpha(alpha)
  ,_beta(beta)
  ,_gamma(gamma)
  ,_maximumStepSize(maxStepSize)
  ,_minimumStepSize(minStepSize)
  , c21(    1.0/4.0)
  , c31(    3.0/32.0)
  , c32(    9.0/32.0)
  , c41( 1932.0/2197.0)
  , c42(-7200.0/2197.0)
  , c43( 7296.0/2197.0)
  , c51(  439.0/216.0)
  , c52(     -8)
  , c53( 3680.0/513)
  , c54( -845.0/4104.0)
  , c61(   -8.0/27.0)
  , c62(      2)
  , c63(-3544.0/2565.0)
  , c64( 1859.0/4104.0)
  , c65(  -11.0/40.0)
  , z1(    16.0/135.0 )
  , z2(  6656.0/12825.0 )
  , z3( 28561.0/56430.0)
  , z4(   - 9.0/50.0)
  , z5(     2.0/55.0)
  , y1(    25.0/216.0)
  , y2(  1408.0/2565.0)
  , y3(  2197.0/4101.0)
  , y4(    -1.0/5.0)
  {
    setStepSize(initialStepSize);
	setName("Runge-Kutta-Fehlberg 4-5");
}