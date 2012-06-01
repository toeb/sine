#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Collision/Detection/Acceleration/Octree.h>
namespace IBDS{
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