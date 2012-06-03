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
   virtual void addCollision(Collision * col){};
   virtual void resetCollisions(){};  
   virtual void reset(){};
   virtual void update(){};
   virtual void handleCollisions(){};
};



class Collidable : public ICollidable{
private:
  std::vector<Collision*> _collisions;
  Geometry & _geometry;
public:
  Collidable(Geometry & go);
  virtual const TypeId getType()const;

  virtual Geometry & getGeometry()const;
  
  const std::vector<Collision*> & getCollisions()const;
  void addCollision(Collision * col);
  void resetCollisions();  
  bool isColliding()const;

  void foreachCollision(std::function<void(Collision *)> f);
};
}