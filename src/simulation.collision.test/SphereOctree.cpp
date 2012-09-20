#include "SphereOctree.h"

#include <simulation.geometry/boundingVolumes/BoundingSphere.h>

using namespace nspace;


 bool SphereOctree::testCollision(const ISimulationObject & obja, const ISimulationObject & objb,Collision * collision)const{

   const Sphere & a = dynamic_cast<const Sphere &>(obja);
  const Octree & b = dynamic_cast<const Octree &>(objb);
  return testCollision(a,b,collision);
}

 bool SphereOctree::testCollision(const Sphere & sphere, const Octree & octree,Collision * collision)const{  
  BoundingSphere & boundingSphere = static_cast< BoundingSphere&> (octree.getBoundingVolume());
  
  //update the bounding sphere involved in this test (this call is cached (the calculation is only done once per timestep)
  boundingSphere.update();

  //on the finest level do the spheretest with parameters
  if(octree.isLeaf()){
    if( test.testCollision(sphere,boundingSphere,collision)){
      return true;
    }else{
      return false;
    }
  }

  // else check to see if current boudning spheres are colliding. if not return false;
  if(!test.testCollision(sphere,boundingSphere,0) ){
    return false;    
  }
  
  boundingSphere.setColliding(true);
    
  //else test collision of the children of the larger octree or the octree which isnot   leaf;
  bool collisionDetected = false;

  for(int i = 0; i < 8; i ++){
    const Octree * child_i = octree.child(static_cast<OctreeNodeId>(i));
    if(!child_i)continue;
      
    if(testCollision(sphere,*child_i,collision))collisionDetected = true;
    //if(collisionDetected)return true;
  }
  
  return collisionDetected;
}
