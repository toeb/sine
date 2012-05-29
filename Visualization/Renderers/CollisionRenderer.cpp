
#include "CollisionRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;
using namespace std;

void CollisionRenderer::render(){
  _collidable.for_each_Collision([this](Collision * c){
    if(c->objectA == &_collidable){
      
      MiniGL::drawPoint(c->pA_wcs,4,MiniGL::red);
      MiniGL::drawVector(c->pA_wcs,c->pA_wcs+c->normal,2,MiniGL::red);
      MiniGL::drawVector(c->pA_wcs,c->pA_wcs - (c->normal*c->penetrationDepth),2,MiniGL::darkblue);
      
      MiniGL::drawPoint(c->pB_wcs,4,MiniGL::green);
      MiniGL::drawVector(c->pB_wcs,c->pB_wcs-c->normal,2,MiniGL::green);
      MiniGL::drawVector(c->pB_wcs,c->pB_wcs + (c->normal*c->penetrationDepth),2,MiniGL::darkblue);
      

    }
  });
}