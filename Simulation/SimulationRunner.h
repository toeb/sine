#pragma once

#include <Simulation/Simulation.h>

namespace IBDS{
class SimulationRunner{
private:
  
  ///< Size of the desired time step
  Real _desiredTimeStepSize;
  ///< The simulation
  Simulation* _simulation;
public:

  /**
   * \brief Default constructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  SimulationRunner();

  /**
   * \brief Destructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  ~SimulationRunner();

  /**
   * \brief Sets the simulation.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \param [in,out] simulation If non-null, the simulation.
   */
  void setSimulation(Simulation* simulation);

  /**
   * \brief Gets the simulation.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \return null if it fails, else the simulation.
   */
  Simulation* getSimulation();

  /**
   * \brief Gets the desired time step size.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \return The desired time step size.
   */
  const Real & getDesiredTimeStepSize()const;

  /**
   * \brief Sets a desired time step size.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \param h The h.
   */
  void setDesiredTimeStepSize(Real h);;

  /**
   * \brief Runs this object.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  virtual void run()=0;


protected:

  /**
   * \brief Executes the timestep operation.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \param dt The dt.
   */
  void doTimestep(Real dt);  

  /**
   * \brief Executes the desired time step changed action.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  virtual void onDesiredTimeStepChanged(){}

  /**
   * \brief Initializes this object.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  virtual void initialize(){};

  /**
   * \brief Cleans up this object.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  void cleanup();
  
};
};