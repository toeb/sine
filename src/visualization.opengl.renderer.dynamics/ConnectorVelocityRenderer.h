#pragma once
#include <visualization/IRenderer.h>
#include <simulation.dynamics/connection/Connector.h>

namespace nspace{
class ConnectorVelocityRenderer : public IRenderer{
private:
  DynamicConnector & _connector;
public:
  ConnectorVelocityRenderer(DynamicConnector & connector);
  void render();
};
}