#pragma once

#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Collision/Collision.h>
#include <Simulation/Collision/Collidable.h>


namespace IBDS{
class CollisionDetector:public virtual SimulationModuleBase<Collidable>{
private:
  std::vector<Collision*> _collisions;
public:
  void resetCollisions();
  CollisionDetector();
  virtual int detectCollisions(Real time, Real h)=0;
  const std::vector<Collision*> & getCollisions()const;
protected:
  void addCollision(Collision*) ;
};
}