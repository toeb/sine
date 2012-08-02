#pragma once
#include <vector>
#include <Simulation/Geometry/Geometry.h>
#include <functional>
#include <algorithm>
#include <Simulation/Collision/Contact.h>
namespace IBDS{
class ICollidable;


/**
 * \brief Collision. 
 *  a collection of contacts and two objects which parttake
 */
class Collision{
	
 private:
  ///< The contacts of this collision
  std::vector<Contact*> _contacts;

  ///< The object a
  ICollidable * _objectA;
  ///< The object b
  ICollidable * _objectB;
  static bool lastCollisionUsed;
  static Collision * lastCollision;
  void setObjectA(ICollidable & obj){_objectA = &obj;};
  void setObjectB(ICollidable & obj){_objectB = &obj;};
public:
  static Collision * create(ICollidable & a, ICollidable & b){
    if(lastCollisionUsed){
      lastCollision = new Collision(a,b);
    }
    lastCollision->setObjectA(a);
    lastCollision->setObjectB(b);
    lastCollisionUsed = true;
    return lastCollision;
  };
  static void freeCollision(Collision * col){
    if(lastCollision == col)lastCollisionUsed = false;
  };
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