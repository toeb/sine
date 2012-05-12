#pragma once
#include <Visualization/RenderEngine.h>
#include <Simulation/SimulationRunner.h>
#include <Simulation/InputHandler.h>
namespace IBDS{
class GlutInputHandler : public InputHandler  {
public:
  /**
   * \brief Gets the instance of the Singleton GlutSimulationRunner.
   *
   * \author Tobi
   * \date 07.05.2012
   *
   * \return null if it fails, else.
   */
  static GlutInputHandler& instance();
 
  bool initialize();

private:
  
  /**
   * \brief private Default constructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  GlutInputHandler();

  /**
   * \brief Destructor.
   *
   * \author Tobi
   * \date 07.05.2012
   */
  ~GlutInputHandler();
};

};