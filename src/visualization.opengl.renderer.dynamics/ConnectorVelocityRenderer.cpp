#include "ConnectorVelocityRenderer.h"
#include <visualization.opengl/MiniGL.h>

using namespace nspace;

ConnectorVelocityRenderer::ConnectorVelocityRenderer(DynamicConnector & connector):_connector(connector){
}
void ConnectorVelocityRenderer::render(){
  const Vector3D & a =_connector.getWorldPosition();
  Vector3D v_a;
  _connector.calculateWorldVelocity(v_a);
  Vector3D b = a+v_a;

  MiniGL::drawVector(a,b,0.01,MiniGL::blue);
}