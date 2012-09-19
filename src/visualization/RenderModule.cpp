#include "RenderModule.h"

using namespace nspace;

void RenderModule::setDesiredFramerate(int hz){
  _desiredFramerate = hz;
  onDesiredFramerateChanged();
}
int RenderModule::getDesiredFramerate()const{
  return _desiredFramerate;
}

RenderModule::RenderModule():_desiredFramerate(60),_viewport(0),_sceneWidth(800), _sceneHeight(600),_renderingInitialized(false){
  setName("RenderModule");
}
RenderModule::~RenderModule(){
}


void RenderModule::setViewport(Viewport * viewport){
	_viewport = viewport;
	viewport->resize(_sceneWidth, _sceneHeight);
}
void RenderModule::render(){
  tick();
  initializeRendering();
  onBeforeRender();
  //do camera transforms
  if(_viewport)_viewport->viewport();
  //render everything
  foreachObject([](IRenderer * renderer){
    if(renderer->ignore())return;
    renderer->render();
  });
  onAfterRender();
  
  tock();
}
void RenderModule::onPotentialSimulationObjectAdd(ISimulationObject * object){
 /* auto viewport = dynamic_cast<Viewport *>(object);
  if(viewport)  {
    setViewport(viewport);

  }*/
}
void RenderModule::resizeScene(int newWidth, int newHeight){ 
  tick();
  _sceneWidth = newWidth;
  _sceneHeight = newHeight;
  //resize viewport
	if(_viewport)_viewport->resize(newWidth,newHeight);
	
	//resize all renderers
  foreachObject([&newWidth,newHeight](IRenderer * renderer){
    renderer->sceneResized(newWidth,newHeight);
  });

  onSceneResized(newWidth,newHeight);
  logInfo("Scene was resized to " << newWidth << "x" << newHeight );
  tock();
}

void RenderModule::initializeRendering(){
  if(_renderingInitialized)return;
  _renderingInitialized = true;
  foreachObject([](IRenderer * renderer){
    renderer->onBeforeRendering();
  });

  logInfo("RenderModule:: rendering initialized");


}
bool RenderModule::initializeObject(){
  if(!initializeRenderEngine())return false;
  return true;

}


void RenderModule::cleanupObject(){  
  cleanupRenderEngine();
}
