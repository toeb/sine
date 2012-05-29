#pragma once
#include <Visualization/IRenderer.h>
#include <Simulation/Collision/Detection/Acceleration/BoundingSphereTree.h>
#include <Simulation/Collision/Detection/Acceleration/Octree.h>
namespace IBDS{
  class OctreeRenderer : public IRenderer{
    Octree & _octree;
  public:
    static int level;
    OctreeRenderer(Octree  & octree):_octree(octree){
 
    }
    void render();
  };
class BoundingSphereHierarchyRenderer : public IRenderer{
private:
  BoundingSphereHierarchy & _hierarchy;
public:
   int level;
  BoundingSphereHierarchyRenderer(BoundingSphereHierarchy& hierarchy):_hierarchy(hierarchy),level(0){}
  void render();
};
}