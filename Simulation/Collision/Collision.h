#pragma once

#include <Math/Vector3D.h>

namespace IBDS{
class Collidable;

struct Collision{
  Collision():objectA(0),objectB(0),handled(false){}

  Collidable * objectA;
  Collidable * objectB;  
  Vector3D pA_wcs;
  Vector3D pB_wcs;
  Vector3D normal;
  Real penetrationDepth;
  bool handled;
};
}