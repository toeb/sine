#pragma once
#include <Math/Vector3D.h>
namespace IBDS{
struct Contact{
  ///< the position in world coordinate where object A collides
  Vector3D pA_wcs;
  ///< the position in world coordinate where object B collides
  Vector3D pB_wcs;
  ///< the collision normal
  Vector3D normal;
  ///< The depth of the penetration
  Real penetrationDepth;
};
}