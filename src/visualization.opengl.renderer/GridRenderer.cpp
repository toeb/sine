#include "GridRenderer.h"

#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>

using namespace nspace;

GridRenderer::GridRenderer():_Sections(20), _Width(20),_Height(20) {
}
void GridRenderer::render(){
  ///glPushAttrib(GL_LIGHTING|GL_COLOR_MATERIAL);
  glPushMatrix();

  //glDisable(GL_LIGHTING);
  //glDisable(GL_COLOR_MATERIAL);
  
  glMaterial(GridMaterial());

  glTransformation(Coordinates());

  Real w2 = Width()/2;
  Real h2 = Height()/2;

 
  Vector3D a,b;

  for(int i = 0; i <= Sections(); i++){
    a(0) = Width() * ((double)i/(double)Sections()-0.5);
    a(1) = 0;
    a(2) = -h2;
    b(0) = Width()*((double)i/(double)Sections()-0.5);
    b(1) = 0;
    b(2) = h2;
    
    glLine(a,b);

    a(0) = -w2;
    a(1) = 0;
    a(2) = Height()*((double)i/(double)Sections()-0.5);
    b(0) = w2;
    b(1) = 0;
    b(2) = Height()*((double)i/(double)Sections()-0.5);
    
    glLine(a,b);
  
  }

  glPopMatrix();
 // glPopAttrib();

};