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
  int _collisionsCount;	// keeps track of the handled collisions
  void addContactJoint(DynamicContact & contact);
  void handleContact(DynamicContact & contact);
public:
  ImpulseBasedCollisionHandler(CollisionDetector & detector, ImpulseBasedDynamicsAlgorithm & dynamics);

  void handleCollisions();
  void reset();
  
  inline CollisionDetector & detector(){
    return _detector;
  }
};
}