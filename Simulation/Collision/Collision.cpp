#include "Collision.h"

#include <Simulation/Collision/Collidable.h>

using namespace IBDS;
using namespace std;

 bool Collision::lastCollisionUsed=true;
   Collision * Collision::lastCollision=0;

Collision::~Collision(){

  foreachContact([](Contact * c){
    delete c;
  });
  _contacts.clear();
}

Collision::Collision(ICollidable & a, ICollidable & b):_objectA(&a), _objectB(&b){

};

int Collision::getContactCount()const{return _contacts.size();}

void Collision::addContact(Contact * contact){
  _contacts.push_back(contact);
}
void Collision::foreachContact(std::function<void (Contact *)> f){
  for_each(_contacts.begin(), _contacts.end(), f);
}

void Collision::combineContacts(Contact & contact){
    
  foreachContact([&contact](Contact * currentContact){
    Vector3D::add(contact.pA_wcs,currentContact->pA_wcs,contact.pA_wcs);
    Vector3D::add(contact.pB_wcs,currentContact->pB_wcs,contact.pB_wcs);
    Vector3D::add(contact.normal,currentContact->normal,contact.normal);
    contact.penetrationDepth += currentContact->penetrationDepth;
  });
    
  Vector3D::multiplyScalar(1.0/_contacts.size(),contact.pA_wcs,contact.pA_wcs );
  Vector3D::multiplyScalar(1.0/_contacts.size(),contact.pB_wcs,contact.pB_wcs );
  contact.penetrationDepth /= _contacts.size();
  contact.normal.normalize();
}


ICollidable & Collision::getObjectA()const{return *_objectA;}
ICollidable & Collision::getObjectB()const{return *_objectB;}


