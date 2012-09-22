#pragma once

#include <simulation.dynamics.force/DampedSpring.h>
#include <visualization/IRenderer.h>

namespace nspace{
  class SpringRenderer:public IRenderer{
  private:
    Real _maxForceAmount;
    DampedSpring & _spring;
  public:
    SpringRenderer(DampedSpring & spring);
    void render();
  };
}