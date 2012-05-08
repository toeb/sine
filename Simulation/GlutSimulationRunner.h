#pragma once
#include <Visualization/RenderEngine.h>
#include <Simulation/SimulationRunner.h>
namespace IBDS{
class GlutSimulationRunner : public SimulationRunner, public RenderEngine {
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
  static GlutSimulationRunner* instance();
 
  bool initialize();

  void cleanup();

  /**
   * \brief Runs the Simulation.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  void run();

  void simulateCallback();
  void renderCallback();
  
protected:

  /**
   * \brief handles a change in desired timestep
   *
   * \author Tobi
   * \date 07.05.2012
   */
  void onDesiredTimeStepChanged();
  void onSimulationSet();

  void onDesiredFramerateChanged();
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