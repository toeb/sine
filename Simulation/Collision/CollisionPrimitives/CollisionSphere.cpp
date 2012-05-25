#include "CollisionSphere.h"

using namespace std;
using namespace IBDS;


void CollisionSphere::update(Real t, Real h){
  setPosition(_object.getPosition());
  setRadius(_object.calculateBoundingSphereRadius());
}