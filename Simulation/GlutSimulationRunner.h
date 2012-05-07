#pragma once
#include <Visualization/Renderer.h>
#include <Simulation/SimulationRunner.h>
namespace IBDS{
class GlutSimulationRunner : public SimulationRunner, public Renderer {
private:
  //fields
public:

  /**
   * \brief Gets the instance of the Singleton GlutSimulationRunner.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \return null if it fails, else.
   */
  static GlutSimulationRunner* instance();

  void initializeRenderer();
  void cleanupRenderer();
  void render();
  /**
   * \brief Runs the Simulation.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  void run();
protected:

  /**
   * \brief handles a change in desired timestep
   *
   * \author Tobi
   * \date 07.05.2012
   */
  void onDesiredTimeStepChanged();
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