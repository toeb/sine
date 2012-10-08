#pragma once

#include <simulation.dynamics.force/DampedSpring.h>
#include <visualization/Renderer.h>

namespace nspace{
  class SpringRenderer:public Renderer{
  private:
    Real _maxForceAmount;
    DampedSpring & _spring;
  public:
    SpringRenderer(DampedSpring & spring);
    void render();
  };
}