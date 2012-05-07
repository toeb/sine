#ifndef __Simulation_h__
#define __Simulation_h__
#include <vector>
#include "SimulationObjects/Force.h"
#include "Integrators/Integrator.h"
#include "ISimulationObject.h"
#include "Integrators/CompositeIntegratable.h"
#include "Integrators/IIntegrable.h"
#include "SimulationObjects/Body.h"
#include "SimulationObjects/Connector.h"
#include "SimulationObjects/Joint.h"

namespace IBDS{
class Simulation{
private:
  Real _time;
  Real _targetTime;
  Integrator* _integrator;
 


  std::vector<ISimulationObject*> & _renderObjects;
  std::vector<Body*> & _bodies;
  CompositeIntegratable & _integables;
  std::vector<Force*> _forces;
  
  std::vector<Connector*> _connectors;
  CompositeIntegratable _integrableConnectors;
  std::vector<Joint*> _joints;

  const char * _simulationName;
  int _commandlineArgumentCount;
  char** _commandlineArgumentArray;
  
  void applyExternalForces();
  void integrate();
protected:

  /**
   * \brief Applies the external forces.
   * 				
   * 				calls applyCustomForces then applies the forces that were added to this simulation
   * 				@see addForce 
   *
   * \author Tobi
   * \date 07.05.2012
   */
  virtual void applyCustomForces(){};
  virtual void beforeIntegration();
  virtual void afterIntegration();
  virtual void buildModel(){};
  virtual void initializeRenderer(); 
  
  virtual void initializeSimulation(){};
  virtual void initializeRenderList(std::vector<ISimulationObject*> & objectsToRender);
  virtual void updateRenderList(std::vector<ISimulationObject*> & objectsToRender){};
public:
  virtual void cleanup(){};
  virtual bool isSimulationValid();
  const Real & getTargetTime();
  const Real & getTime();

  void initialize();

  void setSimulationName(const char * name);
  const char* getSimulationName()const;
  /**
   * \brief Default constructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  Simulation();


  /**
   * \brief Gets the command line
   * \author Tobi
   * \date 07.05.2012
   *
   * \param [out] argc The argc.
   * \param [out] argv If non-null, the argv.
   */
  void getCommandLineArguments(int & argc, char ** argv)const;

  /**
   * \brief Sets the command line arguments.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \param argc          The argc.
   * \param [in,out] argc If non-null, the argc.
   */
  void setCommandLineArguments(int argc, char** argv);
  /**
   * \brief Destructor.
   *
   * \date 07.05.2012
   */
  ~Simulation();

  void setIntegrator(Integrator * integrator);
  Integrator * getIntegrator();

  void addBody(Body * object);
  void addForce(Force *force);
  
  void simulate(Real targetTime);
  
  void render();

  void resetForces();

  void addConnector(Connector *c);
  void addJoint(Joint *joint);
};
}
#endif