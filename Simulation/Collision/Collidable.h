#pragma once

#include <Simulation/Collision/Collision.h>
#include <Simulation/Core/ISimulationObject.h>
#include <vector>
#include <functional>
#include <Simulation/Geometry/Geometry.h>
#include <Simulation/Collision/ICollidable.h>

namespace IBDS{

class Collidable : public ICollidable{
private:
  std::vector<Collision*> _collisions;
  Geometry & _geometry;
public:
  
  /**
   * \brief Gets the type of the collision. returns the type of the geometry as default.  may be overridden
   *
   * \return The type.
   */
  virtual const TypeId getCollisionType()const;


  /**
   * \brief Constructor.
   * 				
   * \param [in,out] geometry The geometry.
   */
  Collidable(Geometry & geometry);


  /**
   * \brief Gets the geometry.
   *
   *
   * \return The geometry.
   */
  virtual Geometry & getGeometry()const;

  /**
   * \brief Adds a collision to this collidable. 
   *
   * \param col - the collision.
   */
  void addCollision(Collision * col);

  /**
   * \brief Resets this object. removing all collisions an calling the virtual resetCollidable method
   *
   * \author Tobi
   * \date 05.06.2012
   */
  void reset();    

  /**
   * \brief Query if this object is colliding.
   *
   *
   * \return true if colliding, false if not.
   */
  bool isColliding()const;

  /**
   * \brief Gets the collisions vector
   *
   * \return the collisions.
   */
  const std::vector<Collision*> & getCollisions()const;

  /**
   * \brief Foreach collision iterator.
   *
   * \param the function f called on every collision.
   */
  void foreachCollision(std::function<void(Collision *)> f);
protected:

  /**
   * \brief Resets the collidable. Called when this object is reset
   */
  virtual void resetCollidable(){};
};
}