#include "CompositeRenderer.h"
#include <algorithm>
#include <functional>
using namespace IBDS;
using namespace std;

void CompositeRenderer::render(){
   for(auto renderer = _renderers.begin(); renderer != _renderers.end(); renderer++){
    (*renderer)->render();
  }
}

void CompositeRenderer::cleanupObject(){
   for(auto renderer = _renderers.begin(); renderer != _renderers.end(); renderer++){
    (*renderer)->cleanup();
  }
}
void CompositeRenderer::onBeforeRenderering(){
  for_each(_renderers.begin(), _renderers.end(), [](IRenderer * r){
    r->onBeforeRenderering();
  });
}
bool CompositeRenderer::initializeObject(){
  bool result = true;
  for(auto renderer = _renderers.begin(); renderer != _renderers.end(); renderer++){
    if(!(*renderer)->initialize())result= false;
  }
  return result;
}
void CompositeRenderer::sceneResized(int newWIdth, int newHeight){
   for(auto renderer = _renderers.begin(); renderer != _renderers.end(); renderer++){
     (*renderer)->sceneResized(newWIdth,newHeight);
  }
}
const vector<IRenderer*> & CompositeRenderer::getRenderers()const{
  return _renderers;
}

void CompositeRenderer::removeRenderer(IRenderer* renderer){
  auto renderers = getRenderers();
  for(auto current = renderers.begin(); current != renderers.end(); current++){
    if(*current == renderer){
      current = renderers.erase(current);
    }
  }
}

void CompositeRenderer::addRenderer(IRenderer * renderer){
  _renderers.push_back(renderer);
}

CompositeRenderer::CompositeRenderer(){
 
}

CompositeRenderer::~CompositeRenderer(){
 
}

void CompositeRenderer::clearRenderers(){
  _renderers.clear();
}