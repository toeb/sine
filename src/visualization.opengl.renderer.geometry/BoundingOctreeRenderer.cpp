#include <visualization.opengl/MiniGL.h>
#include <simulation.geometry/boundingVolumes/BoundingSphere.h>
#include "BoundingOctreeRenderer.h"

using namespace nspace;
using namespace std;
int OctreeRenderer::level =0;
bool OctreeRenderer::doRender =true;
void OctreeRenderer::render(){
  if(!doRender)return;

  MiniGL::pushMatrix();
  
  const Matrix3x3 & R =_octree.getGeometry().coordinates().getTransposedRotationMatrix();
  MiniGL::translate(_octree.getGeometry().coordinates().position());
  MiniGL::multMatrix(R);

  _octree.foreachChildOfLevel(level,[](Octree * octree){
    
    Vector3D center;
    octree->getCenter(center);
    //const BoundingBox & aabb =octree->getBoundingBox();
    float color [4];
    const float * baseColor = MiniGL::cyan;
    BoundingVolume * volume = &(octree->getBoundingVolume());
    
    if(volume->isUpToDate()){
      baseColor = MiniGL::darkCyan;
    }
    if(volume->isColliding()){
      baseColor = MiniGL::red;
    }
    for(int i=0; i < 4; i++){ color[i]= baseColor[i];}
        
    color[3]=0.4;
    

    

    //MiniGL::drawPoint(aabb.min,5,MiniGL::darkblue);
    //MiniGL::drawPoint(aabb.max,5,MiniGL::darkblue);    
    MiniGL::drawPoint(center,5,MiniGL::darkblue);
    
    BoundingSphere * bs = dynamic_cast<BoundingSphere*>(volume);
    if(bs){
      MiniGL::drawSphere(bs->getPositionPCS(),bs->radius(),color,14U);
    }
    //MiniGL::drawCube(&center,&((Matrix3x3::Identity())),aabb.getWidth(), aabb.getHeight(), aabb.getDepth(),color);
    
    //MiniGL::drawSphere();
  });
  
  MiniGL::popMatrix();
}
