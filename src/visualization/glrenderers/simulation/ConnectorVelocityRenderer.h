#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Dynamics/Connection/Connector.h>

namespace IBDS{
class ConnectorVelocityRenderer : public IRenderer{
private:
  Connector & _connector;
public:
  ConnectorVelocityRenderer(Connector & connector);
  void render();
};
}