#pragma once

#include <simulation/Simulation.h>
#include <simulation/SimulationModuleBase.h>
#include <simulation/SimulationTask.h>
namespace nspace{
  class SimulationRunner : public virtual SimulationModuleBase<SimulationTask>{
  protected:
    //these methods need to be implemented by a SimulationRunner
    virtual int executeRunner()=0;
    virtual void stopRunner(){}
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
    void stop();

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