#pragma once
#include <Simulation/Geometry/Geometry.h>
namespace IBDS{

class ImplicitSurface: public Geometry{
private:
  Interval _u;
  Interval _v;
public:
  ImplicitSurface()
};
}