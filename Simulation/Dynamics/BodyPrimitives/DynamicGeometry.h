#pragma once

#include <Simulation/Dynamics/RigidBody.h>
#include <Simulation/Core/CompositeSimulationObject.h>
namespace IBDS{
template<class T>
class DynamicGeometry :public CompositeSimulationObject{
private:
  T & _geometry;
  RigidBody _body;

public:
  KinematicBody & kinematics(){return _body.kinematics();}
  CoordinateSystem & coordinates(){return _body.kinematics();}
  DynamicGeometry(T & geometry, Real mass, const Matrix3x3 & inertiaTensor):
    _body(mass,inertiaTensor),
    _geometry(geometry)
  {
    Geometry & geom = static_cast<Geometry&>(geometry);
    geom.coordinates().position << kinematics().position;
    geom.coordinates().orientation<< kinematics().orientation;

    addChild(&_geometry);
    addChild(&_body);
  }
  
  inline RigidBody & body(){return _body;}
  inline const RigidBody & body()const{return body();}

  inline T & geometry(){return _geometry;}
  inline operator T(void){return geometry();};
};


}