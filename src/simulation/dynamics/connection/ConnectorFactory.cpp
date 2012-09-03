#include "ConnectorFactory.h"
#include <simulation/dynamics/connection/RigidBodyConnector.h>
#include <simulation/dynamics/connection/ParticleConnector.h>
using namespace nspace;


ConnectorFactory * ConnectorFactory::_instance = new ConnectorFactory();

void ConnectorFactory::freeConnector(DynamicConnector * connector){
  delete connector;
}

DynamicConnector * ConnectorFactory::createWithLocalConnectionPoint(DynamicBody & body, const Vector3D & p_ocs){

  RigidBody * rigidBody = dynamic_cast<RigidBody*>(&body);
  if(rigidBody){
   return  RigidBodyConnector::createWithLocalConnectionPoint(*rigidBody,p_ocs);
  }
  Particle * particle = dynamic_cast<Particle*>(&body);

  if(particle){
    return new ParticleConnector(*particle);
  }
}

DynamicConnector * ConnectorFactory::createWithWorldConnectionPoint(DynamicBody & body, const Vector3D & p_wcs){
  TypeId type =  body.getBodyType();
  TypeId rbt= RigidBody::Type;
  if(type==RigidBody::Type){
   RigidBody * rigidBody = static_cast<RigidBody*>(&body);
   return  RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody,p_wcs);

  
  }
  if(type==Particle::Type){
    Particle * particle = static_cast<Particle*>(&body);
    return new ParticleConnector(*particle);
  }  
  return 0;
}
