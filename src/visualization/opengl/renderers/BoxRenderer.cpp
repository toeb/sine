#include "BoxRenderer.h"
#include <Visualization/MiniGL.h>
using namespace std;
using namespace IBDS;

BoxRenderer::BoxRenderer(const Hexahedron & box):
_box(box),
_textRenderer(0), 
_p(box.coordinates().position()){
  boxExtent[0] = box.getXExtent();
  boxExtent[1] = box.getYExtent();
  boxExtent[2] = box.getZExtent();
}
void BoxRenderer::render(){  
  Matrix3x3 RT;
  _box.coordinates().orientation().getMatrix3x3T(RT);

  MiniGL::drawCube(
    &_p,
    &RT,
    (float)boxExtent[0],
    (float)boxExtent[1],
    (float)boxExtent[2],
    MiniGL::gray);
  _textPosition = _p + Vector3D(boxExtent[0]+0.1,0.1,0.1);
  //if(_textRenderer) _textRenderer->render();
}


bool BoxRenderer::initializeObject(){
   const string * name =_box.getName();
   if(!name)return true;
  _textRenderer = new TextRenderer(*name,_textPosition);
  return _textRenderer->initialize();
}