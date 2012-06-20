#pragma once
#include <Simulation/Core/ISimulationObject.h>
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
}