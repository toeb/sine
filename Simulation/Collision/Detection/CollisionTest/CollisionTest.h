#pragma once
#include <Simulation/Collision/Collidable.h>
#include <Simulation/Collision/Collision.h>
namespace IBDS{

class CollisionTest{
private:
public:
  virtual const TypeId getTypeA()const=0;
  virtual const TypeId getTypeB()const=0;

  /**
   * \brief Tests for a collision, setting the collision data if col != 0.
   *
   *
   * \param [in] a   a.
   * \param [in] b   The b.
   * \param [out] col If non-null, the col.
   *
   * \return true if the the geometries collide . else false
   */
  virtual bool testCollision(const ICollidable &a, const ICollidable &b, Collision * col)const=0;
  
};
}