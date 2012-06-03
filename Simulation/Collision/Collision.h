#pragma once
#include <vector>
#include <Simulation/Geometry/Geometry.h>
#include <functional>
#include <algorithm>

namespace IBDS{
class ICollidable;

struct Contact{
  Contact();
  ~Contact();
  Vector3D pA_wcs;
  Vector3D pB_wcs;
  Vector3D normal;
  Real penetrationDepth;
};

class Collision{
private:
  std::vector<Contact*> _contacts;
  ICollidable & _objectA;
  ICollidable & _objectB;
public:
  Collision(ICollidable & a, ICollidable & b);
  ~Collision();


  int getContactCount()const;
  void addContact(Contact * contact);
  void foreachContact(std::function<void (Contact *)> f);

  void combineContacts(Contact & contact);

  ICollidable & getObjectA()const;
  ICollidable & getObjectB()const;
};
}