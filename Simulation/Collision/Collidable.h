#pragma once

#include <Simulation/Collision/Collision.h>
#include <Simulation/Core/ISimulationObject.h>
#include <vector>
#include <functional>
#include <Simulation/Geometry/Geometry.h>
namespace IBDS{
class ICollidable : public virtual ISimulationObject{
public:
   virtual Geometry & getGeometry()const=0;
};


class Collidable : public ICollidable{
private:
  std::vector<Collision*> _collisions;
  Geometry & _geometry;
public:
  Collidable(Geometry & go);
  
  virtual Geometry & getGeometry()const;

  virtual void update(){};
  virtual void reset(){};
  virtual void handleCollisions(){};
  
  void addCollision(Collision * col);
  void resetCollisions();  
  bool isColliding()const;
  const std::vector<Collision*> & getCollisions()const;
  void for_each_Collision(std::function<void(Collision *)> f);
};
}