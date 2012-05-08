#include "RenderEngine.h"

using namespace IBDS;

void RenderEngine::setDesiredFramerate(int hz){
  _desiredFramerate = hz;
  onDesiredFramerateChanged();
}
int RenderEngine::getDesiredFramerate()const{
  return _desiredFramerate;
}

RenderEngine::RenderEngine():_desiredFramerate(60), _renderers(0),_renderManager(0){
  _renderers = new CompositeRenderer();
}
RenderEngine::~RenderEngine(){
  delete _renderers;
}

CompositeRenderer & RenderEngine::getRenderers(){
  return *_renderers;
}
void RenderEngine::render(){
  if(_renderManager){
    _renderManager->updateRendererList(getRenderers());
  }
  
  onBeforeRender();
  getRenderers().render();
  onAfterRender();
}
void RenderEngine::setRenderManager(RenderManager * renderMan){
  if(_renderManager==renderMan)return;
  _renderManager=renderMan;
  getRenderers().clearRenderers();
 
}

bool RenderEngine::initialize(){
   if(_renderManager)_renderManager->initializeRendererList(getRenderers());  
  return _renderers->initialize();
}
void RenderEngine::cleanup(){
  _renderers->cleanup();
}


RenderManager * RenderEngine::getRenderManager(){
  return _renderManager;
}