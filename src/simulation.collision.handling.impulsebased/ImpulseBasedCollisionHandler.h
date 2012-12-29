#pragma once
#include <simulation/SimulationModuleBase.h>
#include <simulation.timing/Timeable.h>

#include <simulation.dynamics.multibody.impulsebased/ImpulseBasedMultiBodyModule.h>
#include <simulation.collision.detection/CollisionDetector.h>

#include <simulation.collision.handling.impulsebased/DynamicContact.h>
#include <simulation.collision.handling.impulsebased/DynamicCollidable.h>

namespace nspace{
  class ImpulseBasedCollisionHandler : public SimulationModuleBase<DynamicCollidable>, public virtual Timeable{
  private:
    CollisionDetector & _detector;
    ImpulseBasedMultiBodyModule & _ibdsAlgorithm;
    int _collisionsCount;	// keeps track of the handled collisions

    void addContactJoint(DynamicContact & contact);
    void handleContact(DynamicContact & contact);
  public:
    ImpulseBasedCollisionHandler(CollisionDetector & detector, ImpulseBasedMultiBodyModule & dynamics);

    /**
    * \brief Handle collisions. Main Method of Collision Handler
    *
    */
    void handleCollisions();

    /**
    * \brief Resets this object. (Cleanup after step e.g. Removing Collisions)
    *
    */
    void reset();

    inline CollisionDetector & detector(){
      return _detector;
    }
  };
}