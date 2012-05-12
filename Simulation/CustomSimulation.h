#ifndef __CustomSimulation_h__
#define __CustomSimulation_h__

#include <Simulation/Simulation.h>


namespace IBDS{
class CustomSimulation : public Simulation{
protected:
  void buildModel();
  void buildAlgorithms();
  void onSimulationObjectAdded(ISimulationObject * simObj);
public:
  using Simulation::setName;
};
}
#endif