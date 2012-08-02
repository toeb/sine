#include "ConnectorVelocityRenderer.h"
#include <Visualization/MiniGL.h>

using namespace IBDS;

ConnectorVelocityRenderer::ConnectorVelocityRenderer(Connector & connector):_connector(connector){
}
void ConnectorVelocityRenderer::render(){
  const Vector3D & a =_connector.getWorldPosition();
  Vector3D v_a;
  _connector.calculateWorldVelocity(v_a);
  Vector3D b = a+v_a;

  MiniGL::drawVector(a,b,0.01,MiniGL::blue);
}