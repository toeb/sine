#pragma once
#include <Simulation/ISimulationObject.h>
namespace IBDS{
class IRenderer:public virtual ISimulationObject{
public:
  virtual void onBeforeRenderering(){}
  virtual void render(){};
  virtual void sceneResized(int newWidth, int newHeight){}
};
}
