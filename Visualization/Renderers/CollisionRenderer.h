#pragma once
#include <Simulation/Collision/Collidable.h>
#include <Visualization/IRenderer.h>
namespace IBDS{
class CollisionRenderer : public virtual IRenderer{
private:
  Collidable & _collidable;
public:
  CollisionRenderer(Collidable & collidable):_collidable(collidable){

  }
  void render();
};
}