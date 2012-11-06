#pragma once
#include <config.h>
#include <math/core.h>
#include <math.functions/Function.h>
namespace nspace{

template<typename TY, typename TCoefficients,typename TXVector = VectorND>
class Polynom : public Function<TY,Real> {
  TCoefficients _Coefficients;

public:
  virtual inline bool evaluate(TY & result, const Real & x){
    int n = math::shorthands::matrix::columnCount(_Coefficients); // order of the polynom
    int m = math::shorthands::matrix::rowCount(_Coefficients); // dimension of the result
    if(!math::shorthands::matrix::resize(result,m,1))return false;
    Real xi =1;
    TXVector xVec;
    if(!math::shorthands::matrix::resize(xVec,n,1))return false;
    
    for(int i=0; i< n; i++){
      math::shorthands::matrix::assignElement(xVec,i,0,xi);
      xi *= x;    
    }
    math::shorthands::matrix::assignMatrix(result, _Coefficients*xVec);
    true;
  }
  
  TCoefficients & Coefficients(){
    return _Coefficients;
  }
  const TCoefficients & Coefficients()const{
    return _Coefficients;
  }
  void setCoefficients(const TCoefficients & coeffs){
    _Coefficients = coeffs;
  }
  TCoefficients getCoefficients()const{
    return _Coefficients;
  }

};


}