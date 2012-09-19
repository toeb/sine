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
  virtual const TypeId getCollisionType()const=0;
  const TypeId getCollisionObjectType()const{return collisionObject().getType();}
  
  virtual ISimulationObject & collisionObject()const=0;

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
  */
  virtual void reset(){};

  /**
  * \brief Updates this object. This method is called before a  collision test is performed.
  * 			 it may be called multiple times, therefore subclasses must decide if multiple calls are ignored
  * 			 
  */
  virtual void update(){};


};
}