#include "OctreeOctree.h"
#include <Simulation/Collision/Detection/BoundingVolumes/BoundingSphere.h>

using namespace IBDS;



bool OctreeOctree::testCollision(const Octree & a, const Octree & b, Collision * collision)const{

  BoundingSphere & sphereA = static_cast< BoundingSphere&> (a.getBoundingVolume());
  BoundingSphere & sphereB= static_cast< BoundingSphere&> (b.getBoundingVolume());
  
  sphereA.update();
  sphereB.update();

  //on the finest level do the spheretest with parameters
  if(a.isLeaf() && b.isLeaf()){
    if( sphereTest.testCollision(sphereA,sphereB,collision)){
      return true;
    }else{
      return false;
    }
  }

  // else check to see if current boudning spheres are colliding. if not return false;
  if(!sphereTest.testCollision(sphereA,sphereB,0) ){
    return false;
    
  }
  //else test collision of the children of the larger octree or the octree which isnot   leaf;
  if(sphereA.getRadius() > sphereB.getRadius()&& !a.isLeaf()){
    //refine a
    for(int i = 0; i < 8; i ++){
      const Octree * child_i = a.child(static_cast<OctreeNodeId>(i));
      if(!child_i)continue;
      testCollision(*child_i,b,collision);
    }
  }else{
    //refine b
    for(int i = 0; i < 8; i ++){
      const Octree * child_i = b.child(static_cast<OctreeNodeId>(i));
      if(!child_i)continue;
      testCollision(a,*child_i,collision);
    }
  }
  
  sphereA.setColliding(true);
  sphereB.setColliding(true);
  
  return true;
}