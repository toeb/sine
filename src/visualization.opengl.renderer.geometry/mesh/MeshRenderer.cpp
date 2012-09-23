#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>
#include <visualization.opengl/MiniGL.h>
#include "MeshRenderer.h"
using namespace nspace;

bool MeshRenderer::initializeObject(){
  return _mesh.initialize();
}
void MeshRenderer::cleanupObject(){
  _mesh.cleanup();
}

void MeshRenderer::render(){
  float speccolor [4] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, _color);
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, _color);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

  glColor3fv(_color);
  
  glBegin(GL_TRIANGLES);
  
  _mesh.foreachFace([](Face * face){   
    if(face->vertices.size()==3){
      for(int i=0; i < 3; i++){
        glNormal(face->vertices[i]->normal);
        glVertex(face->vertices[i]->position);
      }
    }
  });
  glEnd();
}
