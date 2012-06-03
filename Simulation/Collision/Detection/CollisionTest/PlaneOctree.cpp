#include "PlaneOctree.h"

#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>

using namespace IBDS;


const TypeId OctreePlane::getTypeA()const{
  return Octree::type;
}
const TypeId OctreePlane::getTypeB()const{
  return Plane::type;
}

 bool OctreePlane::testCollision(const ICollidable & obja, const ICollidable & objb,Collision * collision)const{
   
  const Octree & a = static_cast<const Octree &>(obja);
   const Plane & b = static_cast<const Plane &>(objb.getGeometry());
  return testCollision(a,b,collision);
}

 bool OctreePlane::testCollision(const Octree & octree, const Plane & plane,Collision * collision)const{
  
  BoundingSphere & boundingSphere = static_cast< BoundingSphere&> (octree.getBoundingVolume());
  
  //update the bounding sphere involved in this test (this call is cached (the calculation is only done once per timestep)
  boundingSphere.update();


  //on the finest level do the spheretest with parameters
  if(octree.isLeaf()){
    if( test.testCollision(boundingSphere,plane,collision)){
      return true;
    }else{
      return false;
    }
  }

  // else check to see if current boudning spheres are colliding. if not return false;
  if(!test.testCollision(boundingSphere,plane,0) ){
    return false;    
  }
  
  boundingSphere.setColliding(true);

  
  //else test collision of the children of the larger octree or the octree which isnot   leaf;
  bool collisionDetected = false;

  for(int i = 0; i < 8; i ++){
    const Octree * child_i = octree.child(static_cast<OctreeNodeId>(i));
    if(!child_i)continue;
      
    if(testCollision(*child_i,plane,collision))collisionDetected = true;
    //if(collisionDetected)return true;
  }
  
  return collisionDetected;
}
