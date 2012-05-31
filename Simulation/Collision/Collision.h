#pragma once
#include <vector>
#include <Simulation/Geometry/Geometry.h>
#include <functional>
#include <algorithm>
namespace IBDS{
  class Collidable;

struct Contact{

  Vector3D pA_wcs;
  Vector3D pB_wcs;
  Vector3D normal;
  Real penetrationDepth;

};

class Collision{
private:
  std::vector<Contact*> contacts;
public:
  void addContact(Contact * contact){
    contacts.push_back(contact);
  }
  void foreachContact(std::function<void (Contact *)> f){
    for_each(contacts.begin(), contacts.end(), f);
  }

  void combineContacts(Contact & contact){
    
    foreachContact([&contact](Contact * currentContact){
      Vector3D::add(contact.pA_wcs,currentContact->pA_wcs,contact.pA_wcs);
      Vector3D::add(contact.pB_wcs,currentContact->pB_wcs,contact.pB_wcs);
      Vector3D::add(contact.normal,currentContact->normal,contact.normal);
      contact.penetrationDepth += currentContact->penetrationDepth;
    });
    
    Vector3D::multiplyScalar(1.0/contacts.size(),contact.pA_wcs,contact.pA_wcs );
    Vector3D::multiplyScalar(1.0/contacts.size(),contact.pB_wcs,contact.pB_wcs );
    contact.penetrationDepth /= contacts.size();
    contact.normal.normalize();
  }
  Collision(Collidable & a, Collidable & b):objectA(a), objectB(b){};
  Collidable & objectA;
  Collidable & objectB;
};
}