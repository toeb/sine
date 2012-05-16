#pragma once

#include <Simulation/Force/DampedSpring.h>
#include <Visualization/IRenderer.h>

namespace IBDS{
  class SpringRenderer:public IRenderer{
  private:
    Real _maxForceAmount;
    const DampedSpring & _spring;
  public:
    SpringRenderer(const DampedSpring & spring);
    void render();
  };
}