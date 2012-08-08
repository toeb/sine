#include "BoxRenderer.h"
#include <visualization/opengl/MiniGL.h>
#include <visualization/core/Image.h>
#include <simulation/core/Simulation.h>
using namespace std;
using namespace nspace;

BoxRenderer::BoxRenderer(const Hexahedron & box):
_box(box),
_textRenderer(0), 
_p(box.coordinates().position()){
  boxExtent(0) = box.getXExtent();
  boxExtent(1) = box.getYExtent();
  boxExtent(2) = box.getZExtent();
}
void BoxRenderer::render(){  
  Matrix3x3 RT;
  _box.coordinates().orientation().toTransposedRotationMatrix(RT);
  //texture.bind();
  MiniGL::drawCube(
    _p,
    RT,
    (float)boxExtent(0),
    (float)boxExtent(1),
    (float)boxExtent(2),
    MiniGL::gray);
  _textPosition = _p + Vector3D(boxExtent(0)+0.1,0.1,0.1);
  //texture.unbind();
  //if(_textRenderer) _textRenderer->render();
}


bool BoxRenderer::initializeObject(){
//  *simulation()<<texture;
  if(!_box.hasName())return true;
  const string & name =_box.getName();
  _textRenderer = new TextRenderer(name,_textPosition);
  return _textRenderer->initialize();
}