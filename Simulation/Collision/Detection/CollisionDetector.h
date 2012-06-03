#pragma once

#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Collision/Collision.h>
#include <Simulation/Collision/Collidable.h>

#include <functional>

namespace IBDS{
class CollisionDetector:public virtual ISimulationModule{
private:
  ///< The collisions that are detected
  std::vector<ICollidable*> _collidables;
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
  virtual bool accepts(ICollidable * collidables)=0;
  void foreachCollidable(std::function<void( ICollidable*)> f);
  virtual void foreachPotentialCollision(std::function<void( ICollidable*,ICollidable*)> f);
  void foreachCombination(std::function<void (ICollidable * a,ICollidable* b)> f);
  void addCollision(Collision * collision);

  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);
};
}