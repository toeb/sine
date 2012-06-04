#include "PlaneRenderer.h"
#include <Visualization\MiniGL.h>
#include <algorithm>
using namespace IBDS;
using namespace std;

PlaneRenderer::PlaneRenderer( Plane & plane):_plane(plane){

}
void PlaneRenderer::render(){
  Vector3D a,b,c,d,n;

  static float color[4];
  color[0] = MiniGL::gray[0];
  color[1] = MiniGL::gray[1];
  color[2] = MiniGL::gray[2];
  color[3] = 0.2;


  Real size = 100;
  a =  _plane.getPositionFromUV(Vector2D(-size,-size));
  b =  _plane.getPositionFromUV(Vector2D(-size,size));
  c =  _plane.getPositionFromUV(Vector2D(size,size));
  d =  _plane.getPositionFromUV(Vector2D(size,-size));

  _plane.getNormal(n);

  MiniGL::drawVector(0.25*(a+b+c+d),0.25*(a+b+c+d)+n,3,MiniGL::blue);
  MiniGL::drawPoint(a,4,MiniGL::blue);
  MiniGL::drawPoint(b,4,MiniGL::blue);
  MiniGL::drawPoint(c,4,MiniGL::blue);
  MiniGL::drawPoint(d,4,MiniGL::blue);

  MiniGL::drawQuad(a,b,c,d,n,color);

}

