#include "SimulationRunnerRenderer.h"
#include <Visualization/MiniGL.h>

using namespace IBDS;

SimulationRunnerRenderer::SimulationRunnerRenderer(SimulationRunner & runner):_simulationRunner(runner){

}
SimulationRunnerRenderer::~SimulationRunnerRenderer(){

}
void SimulationRunnerRenderer::render(){
  Simulation* simulation = _simulationRunner.getSimulation();
  if(!simulation)return;

  
}
bool SimulationRunnerRenderer::initialize(){
  return true;
}
void SimulationRunnerRenderer::cleanup(){

}