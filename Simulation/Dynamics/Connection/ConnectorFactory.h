#pragma once
#include <Simulation/Dynamics/DynamicBody.h>
#include <Math/Vector3D.h>
#include <Simulation/Dynamics/Connection/Connector.h>
namespace IBDS{
  class ConnectorFactory{
  public:
    static Connector * createWithLocalConnectionPoint(DynamicBody& body, const Vector3D & p_ocs = Vector3D::Zero());
    static Connector * createWithWorldConnectionPoint(DynamicBody& body, const Vector3D & p_wcs = Vector3D::Zero());

  };
}