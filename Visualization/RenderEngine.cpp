#include "RenderEngine.h"

using namespace IBDS;

void RenderEngine::setDesiredFramerate(int hz){
  _desiredFramerate = hz;
  onDesiredFramerateChanged();
}
int RenderEngine::getDesiredFramerate()const{
  return _desiredFramerate;
}

RenderEngine::RenderEngine():_desiredFramerate(60),_camera(0){
}
RenderEngine::~RenderEngine(){
}


void RenderEngine::reset(){
  objects().clear();
}

void RenderEngine::render(){
  onBeforeRender();
  //do camera transforms
  if(_camera)_camera->camera();
  //render everything
  foreach([](IRenderer * renderer){
    renderer->render();
  });

  onAfterRender();
}
void RenderEngine::onBeforeSimulationObjectAdd(ISimulationObject * object){
  auto camera = dynamic_cast<Camera *>(object);
  if(camera)  {
    this->_camera = camera; 
  }
}
void RenderEngine::resizeScene(int newWidth, int newHeight){ 
    foreach([&newWidth,newHeight](IRenderer * renderer){
    renderer->sceneResized(newWidth,newHeight);
  });

   onSceneResized(newWidth,newHeight);
}

bool RenderEngine::initializeObject(){
  if(!initializeRenderEngine())return false;

  foreach([](IRenderer * renderer){
    renderer->onBeforeRenderering();
  });

}


void RenderEngine::cleanupObject(){  
  cleanupRenderEngine();
}
