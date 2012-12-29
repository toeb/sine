#include "ParticleRenderer.h"

#include <visualization.opengl/MiniGL.h>
using namespace nspace;

ParticleRenderer::ParticleRenderer(const Particle & particle):_particle(particle){
}
ParticleRenderer::~ParticleRenderer(){delete _pointRenderer;}
void ParticleRenderer::render(){
  MiniGL::drawPoint(_particle.position(),4,MiniGL::black);
}