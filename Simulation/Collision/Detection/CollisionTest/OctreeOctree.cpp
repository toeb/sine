#include "OctreeOctree.h"
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>

using namespace IBDS;


const TypeId OctreeOctree::getTypeA()const{
  return Octree::type;
}
const TypeId OctreeOctree::getTypeB()const{
  return Octree::type;
}

 bool OctreeOctree::testCollision(const ICollidable & obja, const ICollidable & objb,Collision * collision)const{

  const Octree & a = static_cast<const Octree &>(obja);
  const Octree & b = static_cast<const Octree &>(objb);
  return testCollision(a,b,collision);
}

 bool OctreeOctree::testCollision(const Octree & a, const Octree & b,Collision * collision)const{
  BoundingSphere & sphereA = static_cast< BoundingSphere&> (a.getBoundingVolume());
  BoundingSphere & sphereB = static_cast< BoundingSphere&> (b.getBoundingVolume());
  
  //update the bounding spheres involved in this test (this call is cached (the calculation is only done once per timestep)
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
  bool collisionDetected = false;
  if(sphereA.getRadius() > sphereB.getRadius()&& !a.isLeaf()){
    //refine a
    for(int i = 0; i < 8; i ++){
      const Octree * child_i = a.child(static_cast<OctreeNodeId>(i));
      if(!child_i)continue;
      if(testCollision(*child_i,b,collision))collisionDetected = true;
    }
  }else{
    //refine b
    for(int i = 0; i < 8; i ++){
      const Octree * child_i = b.child(static_cast<OctreeNodeId>(i));
      if(!child_i)continue;
      if(testCollision(a,*child_i,collision))collisionDetected= true;
    }
  }
  
  sphereA.setColliding(true);
  sphereB.setColliding(true);
  
  return collisionDetected;
}
