#pragma once
#include <Simulation/Dynamics/DynamicBody.h>
#include <Math/Vector3D.h>
#include <Simulation/Dynamics/Connection/Connector.h>
namespace IBDS{
  class ConnectorFactory{
  private:
  static ConnectorFactory * _instance;
  public:
    static inline ConnectorFactory & instance(){
      return *_instance;
    }
    Connector * createWithLocalConnectionPoint(DynamicBody& body, const Vector3D & p_ocs = Vector3D::Zero());
    Connector * createWithWorldConnectionPoint(DynamicBody& body, const Vector3D & p_wcs = Vector3D::Zero());
    void freeConnector(Connector * connector);
  
  };

}