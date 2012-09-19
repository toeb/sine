#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Dynamics/Connection/Connector.h>
namespace IBDS{

class ConnectorForceRenderer : public IRenderer{
  const Connector & _connector;
  Vector3D _offset;
public:
  ConnectorForceRenderer(const Connector & connector);
  void render();
};
}