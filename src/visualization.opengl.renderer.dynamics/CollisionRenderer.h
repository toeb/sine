#pragma once
#include <simulation.collision/Collidable.h>
#include <simulation.collision.detection/CollisionDetector.h>

#include <simulation/composites/CompositeSimulationObject.h>
#include <visualization/Renderer.h>
#include <queue>

namespace nspace{
  class CollidableRenderer : public virtual Renderer{
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
  class CollisionRenderer : public virtual Renderer{
  private:
    std::vector<RenderContact* > collisions;
    CollisionDetector & _detector;
    Real _timeout;
    bool _trace;
    bool _render;
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
