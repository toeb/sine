#ifndef __Simulation_h__
#define __Simulation_h__
#include <vector>
#include "Force.h"
#include "Integrators/Integrator.h"
#include "ISimulationObject.h"
#include "Integrators/CompositeIntegratable.h"
#include "Integrators/IIntegrable.h"
#include "Simulation/Body.h"

namespace IBDS{
class Simulation{
private:
  Real _time;
  Integrator* _integrator;
  //std::vector<ISimulationObject*> & _simulationObjects;
  std::vector<Body*> & _bodies;
  CompositeIntegratable & _integables;
  std::vector<Force*> _forces;
public:

  Simulation();
  ~Simulation();

  void setIntegrator(Integrator * integrator);
  Integrator * getIntegrator();

  //void addSimulationObject(ISimulationObject * object);
  void addBody(Body * object);

  void addForce(Force *force);
  
  void simulate(Real targetTime);
  void render();

  void resetForces();
};
}
#endif