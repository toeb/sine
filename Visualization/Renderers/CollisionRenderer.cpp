
#include "CollisionRenderer.h"
#include <Visualization/MiniGL.h>
using namespace IBDS;
using namespace std;

void CollidableRenderer::render(){
  _collidable.foreachCollision([this](Collision * c){
    if(&(c->getObjectA()) == &_collidable){
        //Contact p;
        //c->combineContacts(p);

        
        c->foreachContact([](Contact * c){
          Contact & p = *c;
          MiniGL::drawPoint(p.pA_wcs,4,MiniGL::red);
          MiniGL::drawVector(p.pA_wcs,p.pA_wcs+p.normal,2,MiniGL::red);
          MiniGL::drawVector(p.pA_wcs,p.pA_wcs - (p.normal*p.penetrationDepth),2,MiniGL::darkblue);
      
          MiniGL::drawPoint(p.pB_wcs,4,MiniGL::green);
          MiniGL::drawVector(p.pB_wcs,p.pB_wcs-p.normal,2,MiniGL::green);
          MiniGL::drawVector(p.pB_wcs,p.pB_wcs + (p.normal*p.penetrationDepth),2,MiniGL::darkblue);
        });
    }
  });
}

void CollisionRenderer::render(){
  _detector.foreachCollision([](Collision * collision){
    collision->foreachContact([](Contact * contact){
          Contact & p = *contact;
          MiniGL::drawPoint(p.pA_wcs,4,MiniGL::red);
          MiniGL::drawVector(p.pA_wcs,p.pA_wcs+p.normal,2,MiniGL::red);
          MiniGL::drawVector(p.pA_wcs,p.pA_wcs - (p.normal*p.penetrationDepth),2,MiniGL::darkblue);
      
          MiniGL::drawPoint(p.pB_wcs,4,MiniGL::green);
          MiniGL::drawVector(p.pB_wcs,p.pB_wcs-p.normal,2,MiniGL::green);
          MiniGL::drawVector(p.pB_wcs,p.pB_wcs + (p.normal*p.penetrationDepth),2,MiniGL::darkblue);
        });
  });
}