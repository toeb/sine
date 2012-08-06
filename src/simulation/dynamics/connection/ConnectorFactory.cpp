#include "ConnectorFactory.h"
#include <simulation/dynamics/connection/RigidBodyConnector.h>
#include <simulation/dynamics/connection/ParticleConnector.h>
using namespace nspace;


ConnectorFactory * ConnectorFactory::_instance = new ConnectorFactory();

void ConnectorFactory::freeConnector(Connector * connector){
  delete connector;
}

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
  
  if(body.getBodyType()==RigidBody::Type){
   RigidBody * rigidBody = static_cast<RigidBody*>(&body);
   return  RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody,p_wcs);

  
  }
  if(body.getBodyType()==Particle::Type){
    Particle * particle = static_cast<Particle*>(&body);
    return new ParticleConnector(*particle);
  }  
  return 0;
}
