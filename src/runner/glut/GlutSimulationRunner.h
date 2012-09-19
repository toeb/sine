#pragma once

#include <simulation/runner/SimulationRunner.h>
#include <simulation/interaction/InputHandler.h>

namespace nspace{
  class GlutSimulationRunner : public SimulationRunner {
private:
  //fields  
  int _commandlineArgumentCount;
  char** _commandlineArgumentArray;
  
public:
  char ** getCommandLineArguments(int & argc);
  void setCommandLineArguments(int argc, char ** argv);

  /**
   * \brief Gets the instance of the Singleton GlutSimulationRunner.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \return null if it fails, else.
   */
  static GlutSimulationRunner& instance(); 


  /**
   * \brief Runs the Simulation.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  int executeRunner();

  void simulateCallback();
  void renderCallback();
  
protected:
  void cleanupObject();
  
  bool initializeRunner();
  
private:

  /**
   * \brief private Default constructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  GlutSimulationRunner();

  /**
   * \brief Destructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  ~GlutSimulationRunner();
};

};