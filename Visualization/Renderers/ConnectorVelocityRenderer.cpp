#include "ConnectorVelocityRenderer.h"
#include <Visualization/MiniGL.h>

using namespace IBDS;

ConnectorVelocityRenderer::ConnectorVelocityRenderer(Connector & connector):_connector(connector){
}
void ConnectorVelocityRenderer::render(){
  Vector3D a =_connector.getWorldPosition();
  Vector3D b = a + _connector.getWorldVelocity();

  MiniGL::drawVector(a,b,0.01,MiniGL::blue);
}