#pragma once
#include <visualization/Renderer.h>
#include <simulation.dynamics/connection/Connector.h>
namespace nspace{

class ConnectorForceRenderer : public Renderer{
  TYPED_OBJECT(ConnectorForceRenderer)
  const DynamicConnector & _connector;
  Vector3D _offset;
public:
  ConnectorForceRenderer(const DynamicConnector & connector);
  void render();
};
}