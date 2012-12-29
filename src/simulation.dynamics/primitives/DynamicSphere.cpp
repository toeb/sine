#include "DynamicSphere.h"
using namespace nspace;

DynamicSphere::DynamicSphere(Real m, Real r):
  DynamicGeometry(*new Sphere(r),m, DynamicSphere::calculateInertia(m,r)){
}
Matrix3x3 DynamicSphere::calculateInertia(Real m, Real r){
  Matrix3x3 inertia;
  Real scalarInertia = m*r*r*0.4; // 2/5*r²
  inertia = Matrix3x3::Identity();
  inertia = scalarInertia*inertia;
  return inertia;
}