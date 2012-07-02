#include "ConnectorFactory.h"
#include <Simulation/Dynamics/Connection/RigidBodyConnector.h>
#include <Simulation/Dynamics/Connection/ParticleConnector.h>
using namespace IBDS;

  
Connector * ConnectorFactory::createWithLocalConnectionPoint(DynamicBody & body, const Vector3D & p_ocs){

  RigidBody * rigidBody = dynamic_cast<RigidBody*>(&body);
  if(rigidBody){
   return  RigidBodyConnector::createWithLocalConnectionPoint(*rigidBody,p_ocs);
  }
  Particle * particle = dynamic_cast<Particle*>(&body);

  if(particle){
    return new ParticleConnector(*particle);
  }


}

Connector * ConnectorFactory::createWithWorldConnectionPoint(DynamicBody & body, const Vector3D & p_wcs){
  
  if(body.getBodyType()==RigidBody::type){
   RigidBody * rigidBody = static_cast<RigidBody*>(&body);
   return  RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody,p_wcs);

  
  }
  if(body.getBodyType()==Particle::type){
    Particle * particle = static_cast<Particle*>(&body);
    return new ParticleConnector(*particle);
  }
  /*
  RigidBody * rigidBody = dynamic_cast<RigidBody*>(&body);
  if(rigidBody){
   return  RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody,p_wcs);
  }
  Particle * particle = dynamic_cast<Particle*>(&body);

  if(particle){
    return new ParticleConnector(*particle);
  }

  */
  return 0;
}
