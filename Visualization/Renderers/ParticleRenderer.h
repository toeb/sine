#pragma once
#include <Visualization/Renderers/PointRenderer.h>
#include <Simulation/SimulationObjects/Particle.h>
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