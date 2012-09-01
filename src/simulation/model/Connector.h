#pragma once
#include <simulation/core/ISimulationObject.h>
#include <math/definitions.h>
namespace nspace{  

  class Connector : public ISimulationObject{
    Vector3D _offset;
  public:
    const Vector3D & offset()const{
      return _offset;
    }
    Vector3D & offset(){
      return _offset;
    }


  };
}