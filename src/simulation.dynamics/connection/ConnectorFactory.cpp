#include "ConnectorFactory.h"
#include <simulation.dynamics/connection/RigidBodyConnector.h>
#include <simulation.dynamics/connection/ParticleConnector.h>
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
  return 0;
}

DynamicConnector * ConnectorFactory::createWithWorldConnectionPoint(DynamicBody & body, const Vector3D & p_wcs){
  TypeId type =  body.getBodyType();
  if(type==typeof(RigidBody)->getId()){
   RigidBody * rigidBody = static_cast<RigidBody*>(&body);
   return  RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody,p_wcs);

  
  }
  if(type==typeof(Particle)->getId()){
    Particle * particle = static_cast<Particle*>(&body);
    return new ParticleConnector(*particle);
  }  
  return 0;
}
