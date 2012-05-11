#include "ParticleRenderer.h"

using namespace IBDS;


ParticleRenderer::ParticleRenderer(const Particle & particle):_particle(particle){
  _pointRenderer = new PointRenderer(particle.getPosition());
}
ParticleRenderer::~ParticleRenderer(){delete _pointRenderer;}
void ParticleRenderer::render(){
  _pointRenderer->render();
}