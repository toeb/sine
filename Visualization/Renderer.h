#pragma once;
#include "IRenderer.h"
namespace IBDS{

class Renderer:public IRenderer{
private:
  IRenderer * renderer;
public:
  void render();
  virtual void initializeRenderer();
  virtual void cleanupRenderer();
};
}