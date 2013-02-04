#pragma once
#include <visualization/Renderer.h>
#include <simulation.geometry/boundingVolumes/BoundingOctree.h>
namespace nspace{
  class OctreeRenderer : public Renderer{
    Octree & _octree;
  public:
    static int level;
    static bool doRender;
    OctreeRenderer(Octree  & octree);
    void render();
  };

}