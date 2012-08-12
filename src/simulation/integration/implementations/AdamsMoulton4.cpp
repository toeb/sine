// #include "AdamsMoulton4.h"
// 
// using namespace std;
// using namespace nspace;
// 
// //predictor: pk+1 = yk + h/24 (-9 f_{k-3} + 37 f_{k-2} - 59 f_{k-1} + 55 f_{k} )
// //corrector: yk+1 = yk + h/24 (f_{k-2}    - 5 f_{k-1}  + 19 f_{k}   + 9 f_{k+1})
// 
// //lte predictor:  
// 
// //see http://math.fullerton.edu/mathews/n2003/abmmethod/AdamsBashforthProof.pdf
// 
// void AdamsMoulton4::doStep(Real t_i,  Real h_i){
//   if(h_i < h())return;//ignore rest step
//   if(t_i< 6*h_i){   
//     x = initialStep( t_i, x,  h_i);
//     return;
//   }
// 
//   //evaluate the function
//   StateMatrix x_i = f(t_i,x,h_i);  
//   
//   //predictor
//   StateMatrix p =  x + (h_i/24)*(-9.0*f_3+37.0*f_2-59.0*f_1+55.0*f_i);
//   
//   //corrector uses predictor result approximation for f_i+1
//   // alternatively  a fixpoint iteration has to be solved for corrector step
// 
//   StateMatrix x_next = x + (h_i/24)*(f_2-5.0*f_1+19.0*f_i+9.0*f(t_i+h_i,p,h_i));
// 
//   //local truncation error estimate
// /*  TVectorX localTruncationErrorEstimateVector = (x_next-p);
//   TScalar localTruncationErrorEstimate = localTruncationErrorEstimateVector.norm();
// 
//   TScalar eps = 10e-5;
//   TScalar tolerance = 5*10e-6;
// 
//   //simple stepsize correction
//   TScalar err = 19.0/270.0*localTruncationErrorEstimate/(x_next.norm()+eps);
//   cout << getNumberOfSteps()<<" h:"<<h<<" err:"<<err<<endl;
//   if(err > tolerance) {
//     halveStepSize();
//   }
//   else if(err < tolerance/100){
//     doubleStepSize();
//   }*/
//   updateHistory();
//   x= x_next;
// }
// AdamsMoulton4::AdamsMoulton4(Real h0):StepIntegrator(h0){
// 
// }
// void AdamsMoulton4::updateHistory(){
//   f_8=f_7;
//   f_7=f_6;
//   f_6=f_5;
//   f_5=f_4;
//   f_4=f_3;
//   f_3=f_2;
//   f_2=f_1;
//   f_1=f_i;
// }
// 
// void AdamsMoulton4::halveStepSize(){
//   h() = h()/2.0;
//   //interpolate to get new history
//   StateMatrix new_f_3 = (1/128.0)* (-5.0*f_4+28.0*f_3-70.0*f_2+140.0*f_1+35.0*f_i);
//   StateMatrix new_f_1= (1/128.0)* (3.0*f_4-20.0*f_3+90.0*f_2+60.0*f_1-5.0*f_i);
//   f_2 =f_1;
//   f_3 = new_f_3;
//   f_1=new_f_1;
// }
// void AdamsMoulton4::doubleStepSize(){
//   h() = 2.0*h();
//   f_1=f_2;
//   f_2=f_4;
//   f_3=f_6;
//   f_4=f_8;
// }
// 
// StateMatrix AdamsMoulton4::initialStep(Real t_i, const StateMatrix & x_i, Real h){
//   f_i = f(t_i,x_i,h);
//   StateMatrix x_next = x_i+f_i*h;
//   updateHistory();  
//   return x_next;
// }
