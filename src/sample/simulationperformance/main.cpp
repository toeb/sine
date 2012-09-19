#include <simulation.utility/DefaultSimulationSetup.h>
#include <simulation.runner.console/ConsoleRunner.h>
#include <simulation/Simulation.h>
#include <simulation.time/CallbackTask.h>
#include <simulation.time/PeriodicTask.h>
#include <simulation.utility/DynamicsAlgorithm.h>
#include <simulation.dynamics/Particle.h>
#include <iostream>
#include <simulation.integration/Evaluator.h>
#include <simulation.integration/implementations/RungeKutta4.h>
#include <simulation.integration/implementations/ExplicitEuler.h>
using namespace std;
using namespace nspace;

class MyFunc : public ISystemFunction{
public:
  Particle & p;
  MyFunc(Particle & p):p(p){}
  virtual void evaluate( Time t, Time h ) 
  {
    p.calculateCachedValues();
    p.calculateDynamics();
  }

};

int main(int argc, char** argv){
  Particle p;
  p.velocity()=Vector3D(1,0,0);

  MyFunc f(p);
  Evaluator eval(p,&f);

  RungeKutta4 rk4(0.1);
  ExplicitEuler euler(0.1);

  rk4.setEvaluator(&eval);
  euler.setEvaluator(&eval);
  euler.setLowerBound(0);
  euler.setUpperBound(100);
  rk4.setLowerBound(0);
  rk4.setUpperBound(100);
  StepIntegrator & stepper = rk4;
  std::cout << p.position()<<endl;
  for(int i=0; i < 10; i++){
    stepper.step();

    std::cout << "i: "<<i<<" t: "<< stepper.t()<<endl<< p.position()<<endl<<endl;
  }

  /*
  Simulation simulation;


  DefaultSimulationSetup defaultSetup;
 

  ConsoleRunner runner;

  simulation << defaultSetup;
  simulation << runner;
  simulation << new DynamicsAlgorithm();
  for(int i=0; i < 1000000; i++){
    
    simulation << new Particle();
  }
  Particle * p = new Particle();
  p->velocity()=Vector3D(2,3,1);
  simulation<<p;
  
  simulation << new PeriodicTaskDelegate([&defaultSetup,p](Time dt,Time t){
    cout << "stats after "<<t<< " s particle pos"<<endl<<p->position() <<endl;
    defaultSetup.timings.printInfo(cout);

  },0.001,true, defaultSetup.simulationTimeProvider);


  runner.run(0.5);

  return 0;*/
}