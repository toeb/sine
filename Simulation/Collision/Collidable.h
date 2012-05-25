#pragma once

#include <Simulation/Collision/Collision.h>
#include <Simulation/Core/ISimulationObject.h>
#include <vector>
#include <functional>
namespace IBDS{

class Collidable : public virtual ISimulationObject{
private:
  std::vector<Collision*> _collisions;
public:
  virtual void update(){};
  virtual void handleCollisions(){};
  

  void addCollision(Collision * col);
  void resetCollisions();  
  const std::vector<Collision*> & getCollisions()const;
  void for_each_Collision(std::function<void(Collision *)> f);
  
};
}