#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/Vector3D.h>
#include <Math/Quaternion.h>
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

class NormalizedQuaternionValue : public virtual IValue{
private:
  Quaternion & _value;
public:
  NormalizedQuaternionValue(const std::string & name, Quaternion & quat):IValue(name),_value(quat){

  }
  
  virtual void set(const void * value){
    const float * values = reinterpret_cast<const float *>(value);
    _value.w = values[3];
    _value.x = values[0];
    _value.y = values[1];
    _value.z = values[2];
  }
  virtual void get(void * value){
     float * values = reinterpret_cast< float *>(value);
    values[3]=_value.w;
    values[0]=_value.x;
    values[1]=_value.y;
    values[2]=_value.z;
  }
};

}