#include "SkyboxRenderer.h"
#include <visualization.opengl/opengl.h>
#include <visualization.opengl/MiniGL.h>
#include <visualization.opengl/Utility.h>
#include <utility.imaging/Image.h>
#include <visualization.opengl/GlViewport.h>

using namespace nspace;
using namespace nspace::stringtools;

void SkyboxRenderer::propertyChanging(std::string, FileBase){
  Textures().clear();
  Components().clear();
  Textures()|=new Texture(*new PngImage(newvalue+"0.png"));
  Textures()|=new Texture(*new PngImage(newvalue+"1.png"));
  Textures()|=new Texture(*new PngImage(newvalue+"2.png"));
  Textures()|=new Texture(*new PngImage(newvalue+"3.png"));
  Textures()|=new Texture(*new PngImage(newvalue+"4.png"));
  Textures()|=new Texture(*new PngImage(newvalue+"5.png"));
  Textures().foreachElement([this](Texture * t){
    Components()|=t;
    t->initialize();
  });
}

SkyboxRenderer::SkyboxRenderer(){
  setName("SkyboxRenderer");
}

void SkyboxRenderer::render(Viewport & viewport){
}
void SkyboxRenderer::onBeforeRendering(Viewport & viewport){
  if(!Textures())return;
  //
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  auto vp = dynamic_cast<GlViewport*>(&viewport);
  glRotate(vp->Coordinates().orientation().toRotationMatrix().transposed());

  glEnable (GL_BLEND);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  Material m(Color(1,1,1,1));
  glMaterial(m);
  Textures().at(0)->bind();

  glQuad(Vector3D(-3,0,0),Quaternion::Identity(),1.0);

  glDisable(GL_DEPTH_TEST);
  //glCallList(2412);

  Real sz=10.0f;
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
  glColor3f (1,1,1);

  // vectors of box
  Vector3D v1(-sz,-sz,-sz);
  Vector3D v2(-sz,-sz,sz);
  Vector3D v3(-sz,sz,-sz);
  Vector3D v4(-sz,sz,sz);
  Vector3D v5(sz,-sz,-sz);
  Vector3D v6(sz,-sz,sz);
  Vector3D v7(sz,sz,-sz);
  Vector3D v8(sz,sz,sz);

  Textures().at(0)->bind();
  glQuad(v2,v1,v3,v4);

  Textures().at(1)->bind();
  glQuad(v1,v5,v7,v3);

  Textures().at(2)->bind();
  glQuad(v5,v6,v8,v7);

  Textures().at(3)->bind();
  glQuad(v6,v2,v4,v8);

  Textures().at(4)->bind();
  glQuad(v3,v7,v8,v4);

  Textures().at(5)->bind();
  glQuad(v2,v6,v5,v1);

  glDisable(GL_TEXTURE_2D);

  glEnable(GL_DEPTH_TEST);
  glPopMatrix();
}

bool SkyboxRenderer::initializeObject(){
  /*
  Real sz=10.0f;
  glNewList (2412, GL_COMPILE);
  glEnable(GL_TEXTURE_2D);
  Textures().at(0)->bind();
  glBegin(GL_QUADS);
  glColor3f (1,1,1);
  // Das vordere QUAD
  glNormal3f(0,0,1);
  glTexCoord2d(0, 0); glVertex3f(-sz, -sz, sz);
  glTexCoord2d(1, 0); glVertex3f( sz, -sz, sz);
  glTexCoord2d(1, 1); glVertex3f( sz, sz, sz);
  glTexCoord2d(0, 1); glVertex3f(-sz, sz, sz);
  glEnd();

  Textures().at(1)->bind();
  glBegin(GL_QUADS);
  // Das rechte QUAD
  glNormal3f(1,0,0);
  glTexCoord2d(1, 0); glVertex3f( sz, -sz, -sz);
  glTexCoord2d(1, 1); glVertex3f( sz, sz, -sz);
  glTexCoord2d(0, 1); glVertex3f( sz, sz, sz);
  glTexCoord2d(0, 0); glVertex3f( sz, -sz, sz);
  glEnd();

  Textures().at(2)->bind();
  glBegin(GL_QUADS);
  // Das hintere QUAD
  glNormal3f(0,0,-1);
  glTexCoord2d(1, 0); glVertex3f(-sz, -sz, -sz);
  glTexCoord2d(1, 1); glVertex3f(-sz, sz, -sz);
  glTexCoord2d(0, 1); glVertex3f( sz, sz, -sz);
  glTexCoord2d(0, 0); glVertex3f( sz, -sz, -sz);
  glEnd();

  Textures().at(3)->bind();
  glBegin(GL_QUADS);
  // Das linke QUAD
  glNormal3f(-1,0,0);
  glTexCoord2d(0, 0); glVertex3f(-sz, -sz, -sz);
  glTexCoord2d(1, 0); glVertex3f(-sz, -sz, sz);
  glTexCoord2d(1, 1); glVertex3f(-sz, sz, sz);
  glTexCoord2d(0, 1); glVertex3f(-sz, sz, -sz);
  glEnd();

  Textures().at(4)->bind();
  glBegin(GL_QUADS);
  // Das obere QUAD
  glNormal3f(0,1,0);
  glTexCoord2d(0, 1); glVertex3f(-sz, sz, -sz);
  glTexCoord2f(0, 0); glVertex3f(-sz, sz, sz);
  glTexCoord2f(1, 0); glVertex3f( sz, sz, sz);
  glTexCoord2f(1, 1); glVertex3f( sz, sz, -sz);
  glEnd();

  Textures().at(5)->bind();
  glBegin(GL_QUADS);
  // Das untere QUAD
  glNormal3f(0,-1,0);
  glTexCoord2d(1, 1); glVertex3f( sz, -sz, sz);
  glTexCoord2d(0, 1); glVertex3f(-sz, -sz, sz);
  glTexCoord2d(0, 0); glVertex3f(-sz, -sz, -sz);
  glTexCoord2d(1, 0); glVertex3f( sz, -sz, -sz);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glEndList();	*/
  return true;
}