#pragma once

#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Collision/Collision.h>
#include <Simulation/Collision/Collidable.h>

#include <functional>

namespace IBDS{

/**
 * \brief Collision detector.  Abstract class
 *
 * \author Tobi
 * \date 05.06.2012
 */
class CollisionDetector:public virtual ISimulationModule{
private:
  ///< The collisions that are detected
  std::vector<ICollidable*> _collidables;
  std::vector<Collision*> _collisions;
public:

  /**
   * \brief Gets the contact count.
   *
   * \return The contact count.
   */
  int getContactCount();

  /**
   * \brief Gets the collision count.
   *
   * \return The collision count.
   */
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
  void detectCollisions(Real time, Real h);

  /**
   * \brief Gets the collisions that were detected.
   *
   *
   * \return null if it fails, else the collisions.
   */
  const std::vector<Collision*> & getCollisions()const;

  void update();
  void reset();

  
  void foreachCollidable(std::function<void(ICollidable*)> f);
  void foreachCollision(std::function<void (Collision* )>f);
  void foreachContact(std::function<void(Collision *, Contact*)>f);
protected:

  /**
   * \brief Executes the collision detection operation.
   *
   *
   * \param t The t.
   * \param h The h.
   */
  virtual void doCollisionDetection(Real t, Real h)=0;

  virtual bool accepts(ICollidable * collidable)=0;

  /**
   * \brief Foreach potential collision.
   * may be overriden to optimize.  currently tests every 2 combination of objects once
   * \param f the function called for every potential collision
   */
  virtual void foreachPotentialCollision(std::function<void( ICollidable*,ICollidable*)> f);

  /**
   * \brief Foreach combination.
   *
   * \param [in,out] f function called on every 2 combination.
   */
  void foreachCombination(std::function<void (ICollidable * a,ICollidable* b)> f);
  
  //called by subclasses when a collision was detected
  void addCollision(Collision * collision);

  /**
   *  implementation of simulation module.
   */
  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);
};
}