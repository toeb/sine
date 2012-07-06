#include "ConnectorRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;

ConnectorRenderer::ConnectorRenderer(Connector & connector):_connector(connector),_coordinateSystemRenderer(0){
}
void ConnectorRenderer::render(){
  MiniGL::drawVector(_connector.getCachedWorldPosition(),_connector.body().getCenterOfGravity(),0.01,MiniGL::black);
  MiniGL::drawPoint(_connector.getCachedWorldPosition(),4,MiniGL::yellow);
}