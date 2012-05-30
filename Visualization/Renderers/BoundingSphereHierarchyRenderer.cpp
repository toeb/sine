#include <Visualization/MiniGL.h>
#include "BoundingSphereHierarchyRenderer.h"



using namespace IBDS;
using namespace std;
int OctreeRenderer::level =0;
void OctreeRenderer::render(){
  MiniGL::pushMatrix();
  
  const Matrix3x3 & R =_octree.getGeometry().getRotationMatrix();
  MiniGL::translate(_octree.getGeometry().getPosition());
  MiniGL::multMatrix(R);

  _octree.foreachChildOfLevel(level,[](Octree * octree){
    Vector3D center;
    octree->getCenter(center);
    const AABB & aabb =octree->getAABB();
    float color [4];
    for(int i=0; i < 4; i++){ color[i]= MiniGL::cyan[i];}
    color[3]=0.4;
    
    //MiniGL::drawPoint(aabb.min,5,MiniGL::darkblue);
    //MiniGL::drawPoint(aabb.max,5,MiniGL::darkblue);    
    MiniGL::drawPoint(center,5,MiniGL::darkblue);
    
    //MiniGL::drawCube(&center,&((Matrix3x3::Identity())),aabb.getWidth(), aabb.getHeight(), aabb.getDepth(),color);
    
    //MiniGL::drawSphere();
  });
  
  MiniGL::popMatrix();
}

void BoundingSphereHierarchyRenderer::render(){
  
    static float color[4];
  color[0] = MiniGL::darkGreen[0];
  color[1] = MiniGL::darkGreen[1];
  color[2] = MiniGL::darkGreen[2];
  color[3] = 0.2;

  _hierarchy.for_each_in_level(level,[this](BoundingSphereHierarchy* b){
  
    const Vector3D & p  = b->getPosition();
    MiniGL::drawSphere(&p,b->getRadius(),color);
    MiniGL::drawPoint(p, 5,MiniGL::darkYellow); 
  });


}