#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/Vector3D.h>
#include <Visualization/UserInterface/RealValue.h>

namespace IBDS{
class Vector3DValue : public virtual ISimulationObject{
private:
  Vector3D & _value;  
public:  
  RealValue x;
  RealValue y;
  RealValue z;
  Vector3DValue(const std::string & name, Vector3D & value);
};

}