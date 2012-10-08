#pragma once
#include <visualization/Renderer.h>
#include <simulation.dynamics/connection/Connector.h>

namespace nspace{
class ConnectorVelocityRenderer : public Renderer{
private:
  DynamicConnector & _connector;
public:
  ConnectorVelocityRenderer(DynamicConnector & connector);
  void render();
};
}