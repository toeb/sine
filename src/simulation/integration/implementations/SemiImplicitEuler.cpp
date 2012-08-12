// #include "SemiImplicitEuler.h"
// 
// using namespace nspace;
// 
// /**
//   * \brief Constructor.
//   *
//   * \param [in]  system   The system.
//   * \param stepSize          (optional) size of the step (default is 0.01).
//   */
// SemiImplicitEuler::SemiImplicitEuler(Real h0):StepIntegrator(h0){
//   setName("Semi Implicit Euler");
// };
// 
// /**
//   * \brief does a semi implicit Euler step.
//   *
//   * \param t_i The current time t_i.
//   * \param h   The timestep length h.
//   *
//   * \return  .
//   */
// void SemiImplicitEuler::doStep(Real t_i, Real h_i){
//   StateMatrix  f_i = f(t_i, x,h_i);
//   StateMatrix x_next =  x+h_i * f_i;
//   f_i = f(t_i,x_next,h_i);
//   x = x + h_i * f_i;  
// };
// 
// int SemiImplicitEuler::getErrorOrder()const{return 2;}