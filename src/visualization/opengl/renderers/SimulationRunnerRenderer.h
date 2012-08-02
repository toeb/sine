#pragma once
#include <Simulation/runner/SimulationRunner.h>
#include <Visualization/IRenderer.h>
namespace IBDS{
  class SimulationRunnerRenderer:public IRenderer{
  private:
    SimulationRunner & _simulationRunner;
  public:
    SimulationRunnerRenderer(SimulationRunner& runner);
    ~SimulationRunnerRenderer();
    void render();
  protected:
    
  bool initializeObject();
  void cleanupObject();
  };
}