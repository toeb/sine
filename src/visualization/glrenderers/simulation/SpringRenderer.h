#pragma once

#include <Simulation/Force/DampedSpring.h>
#include <Visualization/IRenderer.h>

namespace IBDS{
  class SpringRenderer:public IRenderer{
  private:
    Real _maxForceAmount;
    DampedSpring & _spring;
  public:
    SpringRenderer(DampedSpring & spring);
    void render();
  };
}