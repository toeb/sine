// #include "ImplicitEuler.h"
// #include <iostream>
// using namespace nspace;
// using namespace std;
// 
//  void ImplicitEuler::doStep(Real t_i, Real h){ 
//   int maxIterations = 100;
//   int i=0;
//   StateMatrix tmp;
//   Real diff;
//   //fix point iteration
//   _x_next = x;
//   while(i < _maxIterations){
//     i++;
//     tmp = x + h * f(t_i,_x_next,h);
//     diff = (tmp -_x_next).norm();
//     _x_next = tmp;
//     if(diff < _tolerance)break;    
//   }
// 
//  // if(getNumberOfSteps() % 100==0)cout << "fixpoint iterations needed: "<<i<<endl;
// 
//   x = _x_next;
// };
// 
//   
// ImplicitEuler::ImplicitEuler(Real h0, Real tolerance,int maxIterations):StepIntegrator(h0), _tolerance(tolerance),_maxIterations(maxIterations){
//   setName("ImplicitEuler");
// }
// void ImplicitEuler::logParameters(ostream & o){
//   StepIntegrator::logParameters(o);
//   o << "<parameter name=\"maximumFixedPointIterations\">"<<_maxIterations<<"</parameter>"<<endl;
//   o << "<parameter name=\"fixedPointTolerance\">"<<_tolerance<<"</parameter>"<<endl;
// }
// 
// int ImplicitEuler::getErrorOrder()const{return 2;}
// 
// /** Nicht beachten.  alter code
// 
// struct Function{
//   virtual TVectorX operator()(TVectorX x)=0;
// };
// 
// 
// struct ImplicitEulerFunction:public Function{
//   ImplicitEuler * _implicitEuler;
//   TTime _t;
//   TTime _t_0;
//   TTime _h;
//   const TVectorX & _x_0;
// 
//   ImplicitEulerFunction(ImplicitEuler * e,TTime t, TTime h, const TVectorX & x_0, TTime t_0)
//     :
//   _implicitEuler(e)
//   , _t(t)
//   , _t_0(t_0)
//   , _x_0(x_0)
//   ,_h(h){
//     
//   }
//   TVectorX operator()(TVectorX x){
//     return _x_0 + _h* _implicitEuler->f(0,x) - x;
//   }
// };
// 
// TMatrixX numdiff(Function & f, const TVectorX & x, TTime h = 0.0001){
//   int n =x.size();
//   TMatrixX J(n,n);
//   
//   for(int i=0; i < n; i++){
//     // calculate f(x + h*e_i);
//     TVectorX x_h = x;
//     x_h(i)+= h;
//     x_h = f(x_h);
//     
//     TVectorX finiteDifference_i=(x_h-x)/h; 
//     J.block(i,0,1,n) = finiteDifference_i.transpose();
//   }
//   return J;
// }
// 
// TVectorX quasiNewton(Function & f, const TVectorX & x_0){
//   int n_max=100;
//   int i=0;
//   int alpha =1;
//   TScalar eps = 10e-5;
//   TVectorX x_i = x_0;
//   TVectorX x_next,d, delta_f, f_i, f_next;
//   
//   TMatrixX J_inv, J_update;
//   TScalar change=0;
//   //initialize f_i and f_next
//   f_i = f(x_i);
//   f_next = f_i;
//   // initialize J;
//   TMatrixX J = numdiff(f,x_0);
//   while(i < n_max){       
//     // increment iteration counter
//     i++;
//     //invert J    
//     J_inv = J.inverse();
//     // calculate d vector
//     d = J_inv * (-f_i);
// 
// 
//     x_next = x_i+d;
//     change = d.norm();
// 
// 
//     cout << "---- x_"<<(i-1)<<" ------- "<<change<< " "<<endl;
//     cout << x_i <<endl;
//     
//     if(change < eps)break;
//     
//     
//     f_next = f(x_next);
//     delta_f = f_next-f_i;
//     f_i = f_next;
// 
// 
//     J_update = (1/( (alpha*d).squaredNorm() )* (delta_f- J * alpha * d) * (alpha * d).transpose());
//     J = J + J_update;
//     x_i = x_next;
//     
//       
//   }
//   
//   return x_next;
// 
// }
// 
// TVectorX fixedPointIteration(Function & f, const TVectorX & x_0, int maxIterations, TScalar h, TScalar tolerance=10e-5){
//   TVectorX x_i = x_0;
//   TVectorX x_next;
//   int i=0;
//   TScalar change=0;
//   while(i < maxIterations){
//     x_next = x_0 + h* f(x_i);
//     change = (x_next-x_i).norm();
//     x_i = x_next;
//     if(change < tolerance)break;
//   }
//   return x_i;
// }
// 
// struct TestFunc : public Function{
//   
//   TVectorX operator()(TVectorX x){
//     TVectorX f(x.size());
//     f(0)=x(0);
//     f(1) =x(0)*x(0)+x(1)*x(1);
//     return f;
//   }
// };
// 
// void testFunction(){
//   cout << "test"<<endl;;
//   Function & f = TestFunc();
//   TVectorX x(2);
//   x(0)=3;
//   x(1)=3;
//  // x(1)=3;
//  // x(2)=3;
// //  cout << "f\n"<<x<<"\n:\n"<<f(x)<<endl;
//  // cout << "J_f:\n"<<numdiff(f,x)<<endl;
//   TVectorX x_result =quasiNewton(f,x);
//   cout << "-----------------" <<endl;
//   cout << x_result<<endl;
//   cout << "f----------------"<<endl;
//   cout <<f(x_result);
// }
// 
// struct ImplicitEulerFixpointIterationFunction : public Function{
//   TTime t_i;
//   TVectorX x_i;
//   ImplicitEuler & implicitEuler;
//   
//   TVectorX operator()(TVectorX x){
// 
//   }
// };*/
