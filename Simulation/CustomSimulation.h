#ifndef __CustomSimulation_h__
#define __CustomSimulation_h__
#include <Simulation/Integrators/Implementations/ExplicitEuler.h>
#include <Simulation/Integrators/Implementations/RungeKutta4.h>
#include <Simulation/Integrators/Implementations/RungeKuttaFehlberg45.h>
#include <Simulation/Integrators/Implementations/IntegratorsManager.h>
#include <Visualization/MiniGL.h>
#include <Simulation/Simulation.h>

namespace IBDS{
class CustomSimulation : public Simulation{
private:
  IntegratorsManager* _integratorManager;

protected:
  void initializeSimulation(){
    setSimulationName("Custom Simulation");
    //initialize Integrators.
    Integrator* integrators[3] = {new ExplicitEuler(), new RungeKutta4(0.001), new RungeKuttaFehlberg45()};    
    _integratorManager = new IntegratorsManager(this,integrators,3);
    MiniGL::setIntegratorsManager(_integratorManager);

    setIntegrator(integrators[0]);
  }
  void buildModel();
  void applyExternalForces(){

  }
  
};
}
#endif