#pragma once
#include <simulation/dynamics/connection/Connector.h>
namespace nspace{
class ConnectorRenderer : public IRenderer{
private:
  Connector & _connector;
public:
  ConnectorRenderer(Connector & connector);
  void render();
};
}