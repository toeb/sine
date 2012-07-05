#pragma once
#include <Simulation/Collision/Handling/ImpulseBased/DynamicCollidable.h>
#include <Simulation/Collision/Handling/ImpulseBased/DynamicContact.h>
#include <Simulation/Core/Timing/Timeable.h>
#include <Simulation/Core/SimulationModuleBase.h>

#include <Simulation/MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h>
#include <Simulation/Collision/Detection/CollisionDetector.h>

namespace IBDS{
  
class ImpulseBasedCollisionHandler : public SimulationModuleBase<DynamicCollidable>, public virtual Timeable{
private:
  CollisionDetector & _detector;
  ImpulseBasedMultiBodyModule & _ibdsAlgorithm;
  int _collisionsCount;	// keeps track of the handled collisions
  void addContactJoint(DynamicContact & contact);
  void handleContact(DynamicContact & contact);
public:
  ImpulseBasedCollisionHandler(CollisionDetector & detector, ImpulseBasedMultiBodyModule & dynamics);

  void handleCollisions();
  void reset();
  
  inline CollisionDetector & detector(){
    return _detector;
  }
};
}