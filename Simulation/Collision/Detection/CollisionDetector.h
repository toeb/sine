#pragma once

#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Collision/Collision.h>
#include <Simulation/Collision/Collidable.h>

#include <functional>

namespace IBDS{
class CollisionDetector:public virtual SimulationModuleBase<Collidable>{
private:
  ///< The collisions that are detected
  std::vector<Collision*> _collisions;
public:
  int getContactCount();
  int getCollisionCount();

  /**
   * \brief Resets the collisions.  (deleting all old ones)
   *
   */
  void resetCollisions();

  /**
   * \brief Default constructor.
   *
   */
  CollisionDetector();

  /**
   * \brief Detect collisions.
   * 				
   * \param time The time.
   * \param h    The h.
   *
   * \return .
   */
  virtual void detectCollisions(Real time, Real h)=0;

  /**
   * \brief Gets the collisions that were detected.
   *
   *
   * \return null if it fails, else the collisions.
   */
  const std::vector<Collision*> & getCollisions()const;

  void update();
  void reset();
protected:
  void foreachCombination(std::function<void (Collidable * a, Collidable* b)> f);
  void addCollision(Collision * collision);
};
}