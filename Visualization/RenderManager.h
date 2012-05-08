#pragma once
#include <Simulation/ISimulationObject.h>
#include <Visualization/CompositeRenderer.h>
namespace IBDS{
class RenderManager:public ISimulationObject{
public:
  virtual void initializeRendererList(CompositeRenderer & renderers)=0;
  virtual void updateRendererList(CompositeRenderer & renderers)=0;
  virtual void addRenderer(IRenderer * renderer)=0;
};
};