#include "CompositeRenderer.h"
#include <visualization/core/IRenderer.h>
using namespace std;
using namespace nspace;

/**
 * \brief Renders this object.
 * 				
 * 				just iterates through all renderers and calls render upon them.
 */
void CompositeRenderer::render(){
  for(vector<IRenderer*>::iterator it = renderers.begin(); it != renderers.end(); it++){
    (**it).render();
  }  
}
void CompositeRenderer::addRenderer(IRenderer & renderer){
  renderers.push_back(&renderer);
}

void CompositeRenderer::onBeforeRendering(){
	for(vector<IRenderer*>::iterator it = renderers.begin(); it != renderers.end(); it++){
		(**it).onBeforeRendering();
	}
}
void CompositeRenderer::sceneResized(int width , int height){
	for(vector<IRenderer*>::iterator it = renderers.begin(); it != renderers.end(); it++){
		(**it).sceneResized(width,height);
	}
}

bool CompositeRenderer::initializeObject(){ 
  bool result = true;
  for(vector<IRenderer*>::iterator it = renderers.begin(); it != renderers.end(); it++){
    IRenderer & renderer = **it;
    result &= renderer.initialize();
  }
  return result;
}
void CompositeRenderer::cleanupObject(){
  for(vector<IRenderer*>::iterator it = renderers.begin(); it != renderers.end(); it++){
    (**it).cleanup();
  }
}
