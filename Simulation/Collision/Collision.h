#pragma once
#include <vector>
#include <Simulation/Geometry/Geometry.h>
#include <functional>
#include <algorithm>

namespace IBDS{
class ICollidable;

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

/**
 * \brief Collision. 
 *  a collection of contacts and two objects which parttake
 */
class Collision{
private:
  ///< The contacts of this collision
  std::vector<Contact*> _contacts;

  ///< The object a
  ICollidable & _objectA;
  ///< The object b
  ICollidable & _objectB;
public:

  /**
   * \brief Constructor.
   *
   * \param [in,out] a a.
   * \param [in,out] b The b.
   */
  Collision(ICollidable & a, ICollidable & b);

  /**
   * \brief Destructor. 
   * 				deletes all collisions
   *
   */
  ~Collision();

  /**
   * \brief Gets the number of contact .
   *
   *
   * \return The contact count.
   */
  int getContactCount()const;

  /**
   * \brief Adds a contact to this collision
   *
   * \param the contact.
   */
  void addContact(Contact * contact);

  /**
   * \brief Iterator foreach contact.
   *
   *
   * \param f  the function called on the contacts of this collision.
   */
  void foreachContact(std::function<void (Contact *)> f);

  /**
   * \brief Combines all contacts into a single contact by generating the mean.
   *
   *
   * \param [out] contact The contact.
   */
  void combineContacts(Contact & contact);

  /**
   * \brief accessor for object a
   *
   * \return The object a.
   */
  ICollidable & getObjectA()const;

  /**
   * \brief Accessor for object B
   *
   * \author Tobi
   * \date 05.06.2012
   *
   * \return The object b.
   */
  ICollidable & getObjectB()const;
};
}