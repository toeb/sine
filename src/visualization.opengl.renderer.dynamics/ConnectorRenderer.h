#pragma once
#include <simulation.dynamics/connection/Connector.h>
#include <visualization/IRenderer.h>
namespace nspace{
class ConnectorRenderer : public IRenderer{
private:
  DynamicConnector & _connector;
public:
  ConnectorRenderer(DynamicConnector & connector);
  void render();
};
}