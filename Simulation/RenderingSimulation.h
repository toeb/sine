#pragma once
#include <Simulation/Simulation.h>
#include <Visualization/RenderManager.h>
#include <vector>
namespace IBDS{
  
class RenderingSimulation : public Simulation, public RenderManager{
private:
  std::vector<IRenderer *> _renderersToAdd;
public:
  void updateRendererList(CompositeRenderer & renderers);
  void initializeRendererList(CompositeRenderer & renderers);
  void addRenderer(IRenderer * renderer);
  using Simulation::getName;
  using Simulation::setName;

};

}