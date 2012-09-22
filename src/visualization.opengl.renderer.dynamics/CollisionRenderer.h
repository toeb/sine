#pragma once
#include <simulation.collision/Collidable.h>
#include <simulation.collision.detection/CollisionDetector.h>

#include <simulation/composites/CompositeSimulationObject.h>
#include <visualization/IRenderer.h>
#include <queue>


namespace nspace{
class CollidableRenderer : public virtual IRenderer{
private:
  Collidable & _collidable;
public:
  CollidableRenderer(Collidable & collidable):_collidable(collidable){

  }
  void render();
};
struct RenderContact : public Contact{
  Real startTime;
  Real timeAlive;
};
class CollisionRenderer : public virtual IRenderer{
private:
CollisionDetector & _detector;
std::vector<RenderContact* > collisions;
Real _timeout;
bool _render;
bool _trace;
public:
  
    bool & renderCollisions(){return _render;}
  bool & renderCollisionTrace(){return _trace;}
  Real & timeout(){return _timeout;}
  CollisionRenderer(CollisionDetector & detector):_detector(detector),_timeout(2),_trace(false),_render(true){

  }
  void render();
  void afterStep(Real t, Real h);
};
}