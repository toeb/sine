#include "PlaneRenderer.h"
#include <Visualization\MiniGL.h>
#include <algorithm>
using namespace IBDS;
using namespace std;

PlaneRenderer::PlaneRenderer( Plane & plane):_plane(plane){

}
void PlaneRenderer::render(){
  Vector3D a,b,c,d,n;
  const float * color = MiniGL::darkCyan;
  a =  _plane.vertices().at(0)->p_ocs;
  b =  _plane.vertices().at(1)->p_ocs;
  c =  _plane.vertices().at(2)->p_ocs;
  d =  _plane.vertices().at(3)->p_ocs;

  _plane.getNormal(n);
  MiniGL::drawPoint(a,4,MiniGL::blue);
  MiniGL::drawPoint(b,4,MiniGL::blue);
  MiniGL::drawPoint(c,4,MiniGL::blue);
  MiniGL::drawPoint(d,4,MiniGL::blue);
  MiniGL::drawQuad(a,b,c,d,n,color);

}

