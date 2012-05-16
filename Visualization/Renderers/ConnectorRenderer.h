#pragma once
#include <Simulation/Dynamics/Connector.h>
#include "CoordinateSystemRenderer.h"
namespace IBDS{
class ConnectorRenderer : public IRenderer{
private:
  Connector & _connector;
  CoordinateSystemRenderer * _coordinateSystemRenderer;
public:
  ConnectorRenderer(Connector & connector);
  void render();
};
}