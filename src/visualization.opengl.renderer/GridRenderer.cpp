#include "GridRenderer.h"

#include <visualization.opengl/opengl.h>
#include <visualization.opengl/MiniGL.h>

using namespace nspace;

void GridRenderer::render(){

  glPushMatrix();
  glTranslated(-width/2,y,-height/2);
  double w2 = width/2;
  double h2 = height/2;
  Vector3D a,b;

  for(int i = 0; i <= sections; i++){
    a(0) = width * ((double)i/(double)sections-0.5);
    a(1) = y;
    a(2) = -h2;
    b(0) = width*((double)i/(double)sections-0.5);
    b(1) = y;
    b(2) = h2;
    
    MiniGL::drawVector(a,b, 2.0f,MiniGL::green);


    a(0) = -w2;
    a(1) = y;
    a(2) = height*((double)i/(double)sections-0.5);
    b(0) = w2;
    b(1) = y;
    b(2) = height*((double)i/(double)sections-0.5);
    
    MiniGL::drawVector(a,b, 2.0f,MiniGL::black);
  
  }

  glPopMatrix();

  glEnd();
};