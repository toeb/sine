#include "ConnectorForceRenderer.h"
#include <Visualization/MiniGL.h>

using namespace IBDS;

ConnectorForceRenderer::ConnectorForceRenderer(const Connector & connector):_connector(connector){
  _offset=Vector3D(-1,0,0);
}
void ConnectorForceRenderer::render(){
  const Vector3D & p = _connector.getCachedWorldPosition();
  const Vector3D & f = _connector.getLastForce();
  Real forceLength = f.length();
  Vector3D p2 = f;
  p2 = p+p2;
  MiniGL::drawVector(p,p+_offset,0.1,MiniGL::green);
  MiniGL::drawVector(_offset+p,_offset+p2,0.2*forceLength,MiniGL::darkMagenta);

}