#pragma once
#include <Simulation/Collision/Handling/ImpulseBased/DynamicCollidable.h>
#include <Simulation/Collision/Handling/ImpulseBased/DynamicContact.h>

#include <Simulation/Core/SimulationModuleBase.h>

#include <Simulation/MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h>
#include <Simulation/Collision/Detection/CollisionDetector.h>

namespace IBDS{
  
class ImpulseBasedCollisionHandler : public SimulationModuleBase<DynamicCollidable>{
private:
  CollisionDetector & _detector;
  ImpulseBasedDynamicsAlgorithm & _ibdsAlgorithm;
  void addContactJoint(DynamicContact & contact);
  int _collisionsCount;	// keeps track of the handled collisions
public:
  ImpulseBasedCollisionHandler(CollisionDetector & detector, ImpulseBasedDynamicsAlgorithm & dynamics);
  void handleContact(DynamicContact & contact);
  void handleCollisions();
  void reset();
  
  inline CollisionDetector & detector(){
    return _detector;
  }
};
}