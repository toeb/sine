#pragma once

#include <math/core.h>

namespace nspace{
class MassConfiguration{
private:
  Real _mass;
  Matrix3x3 _inertia;
public:
  MassConfiguration(){
    _inertia.setZero();
    _mass=0;
  }
  Real & mass(){
    return _mass;
  }
  Matrix3x3 & inertia(){
    return _inertia;
  }
  const Real & mass()const{
    return _mass;
  }
  const Matrix3x3 & inertia()const{
    return _inertia;
  }
};
}