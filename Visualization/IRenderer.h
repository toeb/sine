#pragma once
#include <Simulation/ISimulationObject.h>
namespace IBDS{
class IRenderer:public ISimulationObject{
public:
  virtual void render(){};

    /**
   * \brief Initializes this object.
   *
   * \return  true if it succeeds, false if it fails.
   */
  virtual bool initialize(){return true;};

  /**
   * \brief Cleans up this object.
   */
  virtual void cleanup(){};

  virtual void sceneResized(int newWidth, int newHeight){}
};
}
