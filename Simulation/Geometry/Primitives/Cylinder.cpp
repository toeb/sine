#include "Cylinder.h"

using namespace IBDS;
using namespace std;

Cylinder::Cylinder(Real radius, Real height):_radius(radius),_height(height){

}


Real Cylinder::calculateBoundingSphereRadius()const{
  //the center is in the middle of x,y,z values
  return sqrt(_radius*_radius+(_height*_height/4)); 
}