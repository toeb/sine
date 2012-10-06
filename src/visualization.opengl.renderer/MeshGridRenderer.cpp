#include "MeshGridRenderer.h"

#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>
#include <visualization.opengl/MiniGL.h>

using namespace nspace;


void MeshGridRenderer::render(){
  glTransformation(_origin);

  Color gridColor("red");

  Vector3D p;
  for(int i=0; i < _points; i++){
    for(int j =0; j < _points; j++){
      for(int k=0; k < _points; k++){
        p.x() = i* _spacing - ((_points+1)/2)*_spacing;
        p.y() = j* _spacing - ((_points+1)/2)*_spacing;
        p.z() = k* _spacing - ((_points+1)/2)*_spacing;

        float size = 4;
        if((i%_stride==0) &&(j%_stride==0) &&(k%_stride==0)){
          size = 9;
        }
        MiniGL::drawPoint(p,size,gridColor);
      }
    }
  }
  
}