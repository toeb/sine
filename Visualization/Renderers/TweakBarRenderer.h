#pragma once
#include <Visualization/IRenderer.h>
#include <AntTweakBar/AntTweakBar.h>
namespace IBDS{
  
  class TweakBarRenderer :public IRenderer{
  private:
  TwBar  * _tweakBar;
  public:
    bool initialize();
    void cleanup();
    void render();
  };
}