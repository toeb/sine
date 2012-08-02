#pragma once

#include <simulation/core/Simulation.h>
#include <simulation/core/SimulationModuleBase.h>
#include <simulation/core/SimulationTask.h>
namespace nspace{


class SimulationRunner : public virtual SimulationModuleBase<SimulationTask>{
protected:
  //these methods need to be implemented by a SimulationRunner
  virtual int executeRunner()=0;
  virtual bool initializeRunner()=0;
  
  // this method needs to be called by executeRunner
  void executeTasks();
public:

  /**
   * \brief Default constructor.
   *
   */
  SimulationRunner();

  /**
   * \brief Destructor.
   *
   */
  ~SimulationRunner();

    
  /**
   * \brief Runs the simulation.
   *
   */
  int run();

protected:
  

  virtual void onPausedChanged(){}


  /**
   * \brief Initializes the runner. guarantees that the simulation is set and initialized
   *
   * \return  true if it succeeds, false if it fails.
   */
  bool initializeObject();

  
};
};