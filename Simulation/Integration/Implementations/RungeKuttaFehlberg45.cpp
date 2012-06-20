#include "RungeKuttaFehlberg45.h"


using namespace IBDS;
using namespace std;

void RungeKuttaFehlberg45::doStep(Real t_i,VectorND & x_i, Real h){
  
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