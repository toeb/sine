#include "GlutRendererManager.h"
#include <Visualization/MiniGL.h>
#include <freeglut/include/GL/freeglut.h>
#include <iostream>
using namespace std;
using namespace IBDS;

class PrivateGlutRenderer : public GlutRenderer{
public:
  void doResize(int w, int h){
    resizeScene(w,h);
  }
  void doRender(){
    render();
  }
};


PrivateGlutRenderer * _glutRendererInstance=0;
GlutRenderer & GlutRenderer::instance(){
  if(!_glutRendererInstance)_glutRendererInstance=new PrivateGlutRenderer();
  return *_glutRendererInstance;
}

void resizeCallback(int width, int height){
  _glutRendererInstance->doResize(width,height);
}

void renderGlutCallback(){
  _glutRendererInstance->doRender();
}

bool GlutRenderer::initializeRenderEngine(){
  glutReshapeFunc(resizeCallback);
  MiniGL::setClientSceneFunc(renderGlutCallback);
  return true;
}
void GlutRenderer::cleanupRenderEngine(){

}

void GlutRenderer::onSceneResized(int w, int h){
  MiniGL::reshape(w,h);
}
GlutRenderer::GlutRenderer(){}
GlutRenderer::~GlutRenderer(){}