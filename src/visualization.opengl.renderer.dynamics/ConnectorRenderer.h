#pragma once
#include <simulation.dynamics/connection/Connector.h>
#include <visualization/Renderer.h>
namespace nspace{
class ConnectorRenderer : public Renderer{
private:
  DynamicConnector & _connector;
public:
  ConnectorRenderer(DynamicConnector & connector);
  void render();
};
}