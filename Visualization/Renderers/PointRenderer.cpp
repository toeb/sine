#include "PointRenderer.h"
#include <Visualization/MiniGL.h>

using namespace IBDS;

PointRenderer::PointRenderer(const Vector3D & point):_pointCoordinates(point){

}

void PointRenderer::render(){
  MiniGL::drawPoint(_pointCoordinates,3,MiniGL::darkblue);
}