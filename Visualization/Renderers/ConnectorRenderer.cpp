#include "ConnectorRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;

ConnectorRenderer::ConnectorRenderer(Connector & connector):_connector(connector),_coordinateSystemRenderer(0){
  

 // _coordinateSystemRenderer = new CoordinateSystemRenderer(connector.getWorldPosition(),connector.getBody().
}
void ConnectorRenderer::render(){
 // MiniGL::drawVector(_connector.getWorldPosition(),_connector.getBody().getPosition(),0.01,MiniGL::black);
  MiniGL::drawSphere(&(_connector.getWorldPosition()),0.05,MiniGL::yellow);
}