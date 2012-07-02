#include "DynamicBox.h"
using namespace IBDS;
using namespace std;

DynamicBox::DynamicBox(Real m, Real x, Real y, Real z):
  DynamicGeometry(*new Hexahedron(x,y,z),m, calculateInertia(m,x,y,z)){ 

}


Matrix3x3 DynamicBox::calculateInertia(Real m, Real x, Real y , Real z){
  Matrix3x3 inertia;
  inertia.setZero();
  inertia(0,0) = y*y+z*z;
  inertia(1,1) = x*x+z*z;
  inertia(2,2) = x*x+y*y;
  inertia = (1.0/12.0)*m* inertia;
  return inertia;
  
}
