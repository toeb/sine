#include "ParticleRenderer.h"

#include <Visualization/MiniGL.h>
using namespace IBDS;


ParticleRenderer::ParticleRenderer(const Particle & particle):_particle(particle){

}
ParticleRenderer::~ParticleRenderer(){delete _pointRenderer;}
void ParticleRenderer::render(){
  MiniGL::drawPoint(_particle.position(),4,MiniGL::black);
}