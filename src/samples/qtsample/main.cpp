#include <ds.h>
#include <visualization/glrenderers/general/GridRenderer.h>
#include <visualization/glrenderers/general/LightRenderer.h>
using namespace nspace;
int main(int argc, char** argv){
  DefaultSimulationSetup setup;
  QtSimulationRunner runner;
  Simulation simulation;
  simulation << setup;
  simulation << new GridRenderer(0);
  simulation << new MeshGridRenderer();
  simulation << new LightRenderer();
  simulation<<runner;
  runner.run();
}