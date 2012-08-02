#pragma once
#include <math/definitions.h>
namespace nspace{
  
class Axis{
public:
Vector3D p;
Vector3D n;

  Axis(const Vector3D & normal){
    p.setZero();
    n.assign(normal);
  }
  Axis(){
    p.setZero();
    n.set(1,0,0);
  }
  inline Real projectOnAxis(const Vector3D & a) const{
    Vector3D diff;
    Real result;
    Vector3D::subtract(a, p,diff);
    Vector3D::dotProduct(n,diff,result);
    return result;  
  }
};
}