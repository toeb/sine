#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <functional>
namespace IBDS{
class IRenderer:public virtual ISimulationObject{
public:
  virtual void onBeforeRenderering(){}
  virtual void render(){};
  virtual void sceneResized(int newWidth, int newHeight){}
};
class DelegateRenderer : public IRenderer{
private:
  std::function<void()> _renderFunction;
public:
  DelegateRenderer(std::function<void()> renderFunction):_renderFunction(renderFunction){
    
  }
  void render(){
    _renderFunction();
  }
};
}
