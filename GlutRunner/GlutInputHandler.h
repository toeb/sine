#pragma once
#include <Visualization/RenderEngine.h>
#include <Simulation/runner/SimulationRunner.h>
#include <Visualization/InputHandler.h>
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
protected:
  
  bool initializeObject();

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