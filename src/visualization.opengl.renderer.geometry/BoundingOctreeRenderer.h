#pragma once
#include <visualization/IRenderer.h>
#include <simulation.geometry/boundingVolumes/BoundingOctree.h>
namespace nspace{
  class OctreeRenderer : public IRenderer{
    Octree & _octree;
  public:
    static int level;
    static bool doRender;
    OctreeRenderer(Octree  & octree):_octree(octree){
 
    }
    void render();
  };

}