#include "RenderingSimulation.h"

using namespace IBDS;


void RenderingSimulation::updateRendererList(CompositeRenderer & renderers){
  if(_renderersToAdd.size()<=0)return;
  for(auto rendererToAdd = _renderersToAdd.begin(); _renderersToAdd.end()!= rendererToAdd; rendererToAdd++){
    renderers.addRenderer(*rendererToAdd);
  }
  _renderersToAdd.clear();
}
void RenderingSimulation::initializeRendererList(CompositeRenderer & renderers){
  updateRendererList(renderers);
}
void RenderingSimulation::addRenderer(IRenderer * renderer){
  _renderersToAdd.push_back(renderer);
}
