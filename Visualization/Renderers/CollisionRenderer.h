#pragma once
#include <Simulation/Collision/Collidable.h>
#include <Simulation/Collision/Detection/CollisionDetector.h>
#include <Visualization/IRenderer.h>
namespace IBDS{
class CollidableRenderer : public virtual IRenderer{
private:
  Collidable & _collidable;
public:
  CollidableRenderer(Collidable & collidable):_collidable(collidable){

  }
  void render();
};
class CollisionRenderer : public virtual IRenderer{
CollisionDetector & _detector;
public:
  CollisionRenderer(CollisionDetector & detector):_detector(detector){
  }
  void render();
};
}