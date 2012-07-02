#pragma once
#include <Simulation/Collision/Collidable.h>
#include <Simulation/Collision/Detection/CollisionDetector.h>
#include <Simulation/Core/IUpdateable.h>
#include <Simulation/Core/CompositeSimulationObject.h>
#include <Visualization/IRenderer.h>
#include <queue>
namespace IBDS{
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
class CollisionRenderer : public virtual IRenderer, public virtual IUpdatable{
private:
CollisionDetector & _detector;
std::vector<RenderContact* > collisions;
Real _timeout;
bool _trace;
public:
  bool & renderCollisionTrace(){return _trace;}
  Real & timeout(){return _timeout;}
  CollisionRenderer(CollisionDetector & detector):_detector(detector),_timeout(2),_trace(false){

  }
  void render();
  void afterStep(Real t, Real h);
};
}