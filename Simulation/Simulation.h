#pragma once


#include "SimulationObjects/Force.h"
#include "Integrators/Integrator.h"
#include "ISimulationObject.h"
#include "Integrators/CompositeIntegratable.h"
#include "Integrators/IIntegrable.h"
#include "SimulationObjects/Body.h"
#include "SimulationObjects/Connector.h"
#include "SimulationObjects/Joint.h"

#include <vector>


namespace IBDS{

class Simulation:public ISimulationObject{
private:
  Real _time;
  Real _targetTime;
  Integrator* _integrator;
  std::vector<Body*> & _bodies;
  CompositeIntegratable & _integables;
  std::vector<Force*> _forces;
  std::vector<Connector*> _connectors;
  CompositeIntegratable _integrableConnectors;
  std::vector<Joint*> _joints;
  const char * _simulationName;
protected:
  virtual void onSimulationObjectAdded(ISimulationObject * object){};
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
  
public:
  virtual void reset();
  virtual bool isSimulationValid();

  const Real & getTargetTime();
  const Real & getTime();

  bool initialize();

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

private:
  
  void applyExternalForces();
  void integrate();
};
};