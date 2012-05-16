#include "RenderEngine.h"

using namespace IBDS;

void RenderEngine::setDesiredFramerate(int hz){
  _desiredFramerate = hz;
  onDesiredFramerateChanged();
}
int RenderEngine::getDesiredFramerate()const{
  return _desiredFramerate;
}

RenderEngine::RenderEngine():_desiredFramerate(60){
}
RenderEngine::~RenderEngine(){
}

bool RenderEngine::addSimulationObject(ISimulationObject * object){
  bool added = false;
  
  IRenderer * renderer = dynamic_cast<IRenderer*>(object);
  if(renderer){
    _renderers.addRenderer(renderer);
    added =true;
  }
  return added;
}
void RenderEngine::reset(){
  _renderers.clearRenderers();
}

CompositeRenderer & RenderEngine::getRenderers(){
  return _renderers;
}
void RenderEngine::render(){
  onBeforeRender();
  getRenderers().render();
  onAfterRender();
}

void RenderEngine::resizeScene(int newWidth, int newHeight){ 
  _renderers.sceneResized(newWidth,newHeight);  
   onSceneResized(newWidth,newHeight);
}

bool RenderEngine::initializeObject(){
  if(!initializeRenderEngine())return false;
  _renderers.initialize();

}


void RenderEngine::cleanupObject(){
  _renderers.cleanup();
  cleanupRenderEngine();
}
