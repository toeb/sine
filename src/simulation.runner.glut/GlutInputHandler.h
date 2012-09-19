#pragma once


#include <simulation.interaction/InputHandler.h>
namespace nspace{
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