#pragma once
#include <Simulation/SimulationObjects/Connector.h>
namespace IBDS{
class ConnectorRenderer : public IRenderer{
private:
  Connector & _connector;
public:
  ConnectorRenderer(Connector & connector);
  void render();
};
}