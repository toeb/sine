#pragma once
#include <Visualization/IRenderer.h>
#include <AntTweakBar/AntTweakBar.h>
#include <Simulation/InputHandler.h>
namespace IBDS{
  
  class TweakBarRenderer :public IRenderer, public IInputListener{
  private:
  TwBar  * _tweakBar;
  public:
    void onKeyDown(Keys key);
    void onMouseDown(MouseButtons b);
    void onMouseUp(MouseButtons b);
    void onMouseMove(int x, int y, int dx,int dy);
    bool initialize();
    void cleanup();
    void render();    
    void sceneResized(int newWidth, int newHeight);
  };
}