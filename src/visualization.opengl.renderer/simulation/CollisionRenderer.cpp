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

void CollisionRenderer::afterStep(Real t, Real h){
  if(!renderCollisionTrace())return;
  vector<RenderContact*> toDelete;
  for(int i=0; i < collisions.size(); i++){
    RenderContact * rc = collisions.at(i);
    rc->timeAlive = t-rc->startTime;
    if(rc->timeAlive > timeout()){
      toDelete.push_back(rc);
    }
  }

  for_each(toDelete.begin(), toDelete.end(), [this](RenderContact * renderContact){
    auto it = find(collisions.begin(), collisions.end(), renderContact);
    if(it==collisions.end())return;
    collisions.erase(it);
  });

  vector<RenderContact*> & q = this->collisions;
  _detector.foreachCollision([&q, &t](Collision * collision){
    vector<RenderContact*> & q2 = q;
    Real t2 = t;
    collision->foreachContact([&q2,&t2](Contact * contact){
          RenderContact * newContact = new RenderContact();
          newContact->normal = contact->normal;
          newContact->pA_wcs = contact->pA_wcs;
          newContact->pB_wcs = contact->pB_wcs;
          newContact->startTime = t2;
          q2.push_back(newContact);
        });
  });
}



void CollisionRenderer::render(){
  if(!_render)return;
  if(renderCollisionTrace()){
  for_each(collisions.begin(), collisions.end(), [this](RenderContact * rc){
    Contact & p = *rc;
    float alpha = (timeout()-rc->timeAlive)/timeout();
   if(alpha < 0)alpha = 0;
   if(alpha > 1)alpha = 1;
      float color[4];
      MiniGL::alpha(MiniGL::blue, alpha, color);
      MiniGL::drawPoint(p.pA_wcs,4,color);
      MiniGL::drawVector(p.pA_wcs,p.pA_wcs+p.normal,2,color);

      MiniGL::alpha(MiniGL::green, alpha, color);      
      MiniGL::drawPoint(p.pB_wcs,4,color);
      MiniGL::drawVector(p.pB_wcs,p.pB_wcs-p.normal,2,color);

      
      MiniGL::alpha(MiniGL::darkblue, alpha, color);      
      MiniGL::drawVector(p.pA_wcs,p.pA_wcs - (p.normal*p.penetrationDepth),2,color);
      MiniGL::drawVector(p.pB_wcs,p.pB_wcs + (p.normal*p.penetrationDepth),2,color);
  });
  }
  _detector.foreachContact([](Collision * c, Contact * contact){
    
    Contact & p = *contact;
      MiniGL::drawPoint(p.pA_wcs,2,MiniGL::blue);
      MiniGL::drawVector(p.pA_wcs,p.pA_wcs+p.normal,1,MiniGL::blue);


      MiniGL::drawPoint(p.pB_wcs,1,MiniGL::green);
      MiniGL::drawVector(p.pB_wcs,p.pB_wcs-p.normal,1,MiniGL::green);

          
      MiniGL::drawVector(p.pA_wcs,p.pA_wcs - (p.normal*p.penetrationDepth),1,MiniGL::darkblue);
      MiniGL::drawVector(p.pB_wcs,p.pB_wcs + (p.normal*p.penetrationDepth),1,MiniGL::darkblue);
  });
}