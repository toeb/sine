#pragma once
#include <functional>
#include <core/Object.h>
#include <core.hub/HubObject.h>
namespace nspace{
class Viewport;
class Renderer:public virtual HubObject{
public:
  virtual void onBeforeRendering(Viewport & viewport){onBeforeRendering();}
  virtual void onBeforeRendering(){}
  virtual void render(Viewport & viewport){render();};
  virtual void render(){}
  virtual void sceneResized(int newWidth, int newHeight,Viewport & viewport){}
};

class DelegateRenderer : public Renderer{
private:
  std::function<void()> _renderFunction;
public:
  DelegateRenderer(std::function<void()> renderFunction):_renderFunction(renderFunction){
    
  }
  void render(Viewport & viewport){
    _renderFunction();
  }
};
}
