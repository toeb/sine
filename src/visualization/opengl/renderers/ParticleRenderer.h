#pragma once
#include <Visualization/Renderers/PointRenderer.h>
#include <Simulation/Dynamics/Particle.h>
namespace IBDS{
  class ParticleRenderer : public IRenderer{
  private:
    const Particle & _particle;
    PointRenderer * _pointRenderer;
  public:
    ParticleRenderer(const Particle & particle);
    ~ParticleRenderer();
    void render();
  };
}