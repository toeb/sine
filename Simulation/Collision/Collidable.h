#pragma once

#include <Simulation/Collision/Collision.h>
#include <Simulation/Core/ISimulationObject.h>
#include <vector>
#include <functional>
#include <Simulation/Geometry/Geometry.h>
namespace IBDS{

/**
 * \brief ICollidable interface. 
 *
 * represents an object that has a geometry which can be tested for collision and also 
 * has the interface methods for handling collisions
 * 
 */
class ICollidable : public virtual ISimulationObject{
public:
  
  /**
   * \brief Gets the type of the collision.
   *
   * \return The type.
   */
  virtual const TypeId getCollisionType()const=0;
   /**
    * \brief Gets the geometry which represents the Collidable.
    *
    * \return The geometry.
    */
   virtual Geometry & getGeometry()const=0;

   /**
    * \brief Add a collision to the collidable. 
    *
    *
    * \param [in,out] col If non-null, the col.
    */
   virtual void addCollision(Collision * col){};
   
   /**
    * \brief Resets this object.
    *
    * \author Tobi
    * \date 05.06.2012
    */
   virtual void reset(){};

   /**
    * \brief Updates this object. This method is called before a  collision test is performed.
    * 			 it may be called multiple times, therefore subclasses must decide if multiple calls are ignored
    *
    * \author Tobi
    * \date 05.06.2012
    */
   virtual void update(){};

   /**
    * \brief Handles the collisions.
    *
    */
   virtual void handleCollisions(){};
};



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