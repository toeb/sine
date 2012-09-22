#pragma once
#include <visualization/IRenderer.h>
#include <simulation.dynamics/connection/Connector.h>
namespace nspace{

class ConnectorForceRenderer : public IRenderer{
  const DynamicConnector & _connector;
  Vector3D _offset;
public:
  ConnectorForceRenderer(const DynamicConnector & connector);
  void render();
};
}