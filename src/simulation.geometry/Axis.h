#pragma once
#include <math/definitions.h>
namespace nspace{
  
class Axis{
public:
Vector3D p;
Vector3D n;

  Axis(const Vector3D & normal){
    p.setZero();
    n=normal;
  }
  Axis(){
    p.setZero();
    n = Vector3D::UnitX();
    Vector3D p;
  }
  inline Real projectOnAxis(const Vector3D & a) const{
   // Vector3D diff;
    Vector3D diff = a-p;
    Real result = n*diff;

    /*
    Vector3D::subtract(a, p,diff);
    Vector3D::dotProduct(n,diff,result);*/
    return result;  
  }
};
}