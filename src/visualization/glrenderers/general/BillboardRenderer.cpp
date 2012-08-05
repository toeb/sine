#include "BillboardRenderer.h"
#include <visualization/opengl/opengl.h>
#include <visualization/opengl/Utility.h>
#include <simulation/core/Simulation.h>
#include <lodepng.h>
using namespace std;
using namespace nspace;

bool BillboardRenderer::initializeObject(){
 _texture = new Texture(*new PngImage("resources/image/testimage.png"));
 *simulation()<<_texture;
  return true;
}
void BillboardRenderer::cleanupObject(){

}
void BillboardRenderer::render(){
 _texture->bind();
  glBegin (GL_QUADS);
  glTexCoord2f (0.0, 0.0);
  glVertex3f (0.0, 0.0, 0.0);
  glTexCoord2f (1.0, 0.0);
  glVertex3f (10.0, 0.0, 0.0);
  glTexCoord2f (1.0, 1.0);
  glVertex3f (10.0, 10.0, 0.0);
  glTexCoord2f (0.0, 1.0);
  glVertex3f (0.0, 10.0, 0.0);
  glEnd ();
  _texture->unbind();
}

BillboardRenderer::BillboardRenderer(){

}