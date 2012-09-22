#pragma once

#include <vector>

#include <math/core.h>
namespace nspace{
struct Contact{
  ///< the position in world coordinate where object A collides
  Vector3D pA_wcs;
  ///< the position in world coordinate where object B collides
  Vector3D pB_wcs;
  ///< the collision normal
  Vector3D normal;
  ///< The depth of the penetration
  Real penetrationDepth;
};
class ContactPool{
private:
  std::vector<Contact *> _pool;
  static ContactPool * _instance;
public:
  static inline ContactPool& instance(){
    return *_instance;
  }
  
  inline Contact * createContact(){
    if(_pool.empty()){
      return new Contact();
    }
    Contact * result = _pool.back();
    _pool.pop_back();
    return result;
  }
  inline void freeContact(Contact * contact){
    _pool.push_back(contact);
  }
};
}