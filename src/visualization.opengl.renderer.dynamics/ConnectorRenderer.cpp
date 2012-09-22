#include "ConnectorRenderer.h"
#include <visualization.opengl/MiniGL.h>
using namespace nspace;

ConnectorRenderer::ConnectorRenderer(DynamicConnector & connector):_connector(connector){
}
void ConnectorRenderer::render(){
  MiniGL::drawVector(_connector.getCachedWorldPosition(),_connector.body().getCenterOfGravity(),0.01,MiniGL::black);
  MiniGL::drawPoint(_connector.getCachedWorldPosition(),4,MiniGL::yellow);
}