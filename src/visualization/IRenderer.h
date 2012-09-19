#pragma once
#include <functional>
#include <simulation/ISimulationObject.h>
namespace nspace{
class IRenderer:public virtual ISimulationObject{
private:
  bool _ignoreRenderer;
public:
  IRenderer():_ignoreRenderer(false){}
  inline bool ignore(){return _ignoreRenderer;}
  void setIgnore(bool ignore){_ignoreRenderer = ignore;}
  virtual void onBeforeRendering(){}
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
