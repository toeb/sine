#pragma once
#include <vector>
#include <functional>

#include <simulation/ISimulationObject.h>
#include <simulation.geometry/Geometry.h>
#include <simulation.collision/Collision.h>
#include <simulation.collision/ICollidable.h>

namespace nspace{
  class Collidable : public ICollidable{
    TYPED_OBJECT(Collidable);
  private:
    std::vector<Collision*> _collisions;
    ISimulationObject & _collisionObject;
    const Type::TypeId _collisionType;

  public:

    /**
    * \brief Gets the type of the collision object.
    * \return The type.
    */
    const Type::TypeId getCollisionType()const;

    /**
    * \brief Constructor with no associated rigid body specified.
    * This way, no collision handling will be performed, either on this collidable, or on other collidables colliding with this one.
    *
    * \param [in,out] geometry The geometry.
    */
    Collidable(ISimulationObject & collisionObject);

    /**
    * \brief Gets the collision object which is actually used in collision tests
    *
    *
    * \return .
    */
    inline virtual ISimulationObject & collisionObject()const{return _collisionObject;}

    /**
    * \brief Adds a collision to this collidable.
    *
    * \param col - the collision.
    */
    void addCollision(Collision * col);

    /**
    * \brief Resets this object. removing all collisions an calling the virtual resetCollidable method
    *
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
    const std::vector<Collision*> & collisions()const;

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