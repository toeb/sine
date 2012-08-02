#include <ds.h>
using namespace nspace;
int main(int argc, char** argv){
  DefaultSimulationSetup setup;
  QtSimulationRunner runner;
  Simulation simulation;
  simulation << setup;
  simulation<<runner;
  runner.run();
}