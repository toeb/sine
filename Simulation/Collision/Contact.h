#pragma once
#include <Math/Vector3D.h>
#include <vector>
namespace IBDS{
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
  
  inline Contact * create(){
    if(_pool.empty()){
      return new Contact();
    }
    Contact * result = _pool.back();
    _pool.pop_back();
    return result;
  }
  inline void free(Contact * contact){
    _pool.push_back(contact);
  }
};
}