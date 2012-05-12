#include "CompositeRenderer.h"

using namespace IBDS;
using namespace std;

void CompositeRenderer::render(){
   for(auto renderer = _renderers->begin(); renderer != _renderers->end(); renderer++){
    (*renderer)->render();
  }
}

void CompositeRenderer::cleanup(){
   for(auto renderer = _renderers->begin(); renderer != _renderers->end(); renderer++){
    (*renderer)->cleanup();
  }
}

bool CompositeRenderer::initialize(){
  bool result = true;
  for(auto renderer = _renderers->begin(); renderer != _renderers->end(); renderer++){
    if(!(*renderer)->initialize())result= false;
  }
  return result;
}
void CompositeRenderer::sceneResized(int newWIdth, int newHeight){
   for(auto renderer = _renderers->begin(); renderer != _renderers->end(); renderer++){
     (*renderer)->sceneResized(newWIdth,newHeight);
  }
}
const vector<IRenderer*> & CompositeRenderer::getRenderers()const{
  return *_renderers;
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
  _renderers->push_back(renderer);
}

CompositeRenderer::CompositeRenderer():_renderers(0){
  _renderers = new vector<IRenderer*>();
}

CompositeRenderer::~CompositeRenderer(){
  delete _renderers;
}

void CompositeRenderer::clearRenderers(){
  _renderers->clear();
}