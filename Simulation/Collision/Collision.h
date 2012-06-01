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
  std::vector<Contact*> _contacts;
  Collidable & _objectA;
  Collidable & _objectB;
public:
  int getContactCount()const{return _contacts.size();}
  ~Collision(){
    foreachContact([](Contact * c){
      delete c;
    });
    _contacts.clear();
  }
  void addContact(Contact * contact){
    _contacts.push_back(contact);
  }
  void foreachContact(std::function<void (Contact *)> f){
    for_each(_contacts.begin(), _contacts.end(), f);
  }

  void combineContacts(Contact & contact){
    
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


  Collision(Collidable & a, Collidable & b):_objectA(a), _objectB(b){};

  Collidable & getObjectA()const{return _objectA;}
  Collidable & getObjectB()const{return _objectB;}
};
}