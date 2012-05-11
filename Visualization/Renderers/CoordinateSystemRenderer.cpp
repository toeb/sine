#include "CoordinateSystemRenderer.h"

#include <Visualization/MiniGL.h>

using namespace IBDS;

CoordinateSystemRenderer::CoordinateSystemRenderer():
    _origin(*(new Vector3D())),
      _orientation(*(new Quaternion(1,0,0,0)))
    {
  
}

  CoordinateSystemRenderer::CoordinateSystemRenderer(const Vector3D& origin, const Quaternion & orientation):
    _origin(origin),_orientation(orientation){

  }
  void CoordinateSystemRenderer::render(){
    _orientation.getMatrix3x3T(_orientationMatrix);
    MiniGL::drawVector(_origin,_origin+_orientationMatrix.v[0],0.1f,MiniGL::red);
    MiniGL::drawVector(_origin,_origin+_orientationMatrix.v[1],0.1f,MiniGL::green);
    MiniGL::drawVector(_origin,_origin+_orientationMatrix.v[2],0.1f,MiniGL::blue);
  }