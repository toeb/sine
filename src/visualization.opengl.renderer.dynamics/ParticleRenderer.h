#pragma once
#include <visualization.opengl.renderer.geometry/PointRenderer.h>
#include <simulation.dynamics/Particle.h>

namespace nspace{
  class ParticleRenderer : public Renderer{
  private:
    const Particle & _particle;
    PointRenderer * _pointRenderer;
  public:
    ParticleRenderer(const Particle & particle);
    ~ParticleRenderer();
    void render();
  };
}