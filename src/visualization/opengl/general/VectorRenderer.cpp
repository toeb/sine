#include <vis/opengl/MiniGL.h>

#include "VectorRenderer.h"
#include "mbs/types.h"
using namespace mbslib;

VectorRenderer::VectorRenderer(TVector3 & position, TVector3 & vector,TVector3 & color)
  :_position(position), _vector(vector),_color(color){
  
};

void VectorRenderer::render(){
  float color[4];
  color[0]  =_color(0);
  color[1]  =_color(1);
  color[2]  =_color(2);
  color[3]  =1;
  MiniGL::drawVector(_position, _position+_vector, 2.0, color);
};