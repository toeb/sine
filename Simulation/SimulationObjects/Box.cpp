#include "Box.h"
using namespace IBDS;
using namespace std;
Box::Box() {}
Box::~Box() {}

Box::Box(Real m, Real x, Real y, Real z) : _x(x), _y(y), _z(z) {
  RigidBody::setMass(m);

  Matrix3x3 inertia;
  inertia(0,0) = y*y+z*z;
  inertia(1,1)= x*x+z*z;
  inertia(2,2)  = x*x+y*y;
  inertia = (1.0/12.0)*m* inertia;
  RigidBody::setInertiaTensor(inertia);
  }
bool Box::initialize(){
   _length = 0;
    _name="";
    const string * name = getName();
    if(name){
      _name = getName()->c_str();
      _length = getName()->length();
    }
    return true;
}
void Box::render() {

  Matrix3x3 R;
  Quaternion q = RigidBody::getOrientation();
  q.getMatrix3x3T(R);
  MiniGL::drawCube(&getPosition(),&R,(float)_x,(float)_y,(float)_z,MiniGL::gray);

  Vector3D position(_x/2+0.1,0,0);
 
  MiniGL::drawStrokeText(position+getPosition(),0.003f,_name,_length,MiniGL::darkblue);
}