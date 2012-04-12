#ifndef __RigidBody_h__
#define __RigidBody_h__
#include <Math/Matrix3x3.h>
#include <Math/Quaternion.h>
#include "Particle.h"
#include <Math/Vector3D.h>
namespace IBDS{

/**
 * \brief Rigid body class.  
 * 				Describes a Rigid Body.  Is an extension of Particle
 * 				 
 *
 * \author Tobias Becker
 * \date 10.04.2012
 */
class RigidBody : public Particle{
private:
  ///< The inertia tensor
  IBDS::Matrix3x3 _inertiaTensor;
  ///< The orientation
  IBDS::Quaternion _orientation;
  ///< The angular velocity
  IBDS::Vector3D _angularVelocity;
  ///< The angular acceleration
  IBDS::Vector3D _angularAcceleration;
  ///< The force accumulator
  IBDS::Vector3D _forceAccumulator;
  ///< The torque accumulator
  IBDS::Vector3D _torqueAccumulator;
public:
  
  /**
   * \brief Creates a rigid body representing a sphere.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param mass   The mass.
   * \param radius The radius.
   *
   * \return the rigid body
   */
  static RigidBody* createSphere(Real mass, Real radius);

  /**
   * \brief Creates a cylinder.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param mass   The mass.
   * \param radius The radius.
   * \param length The length.
   *
   * \return null if it fails, else.
   */
  static RigidBody* createCylinder(Real mass, Real radius, Real length);

  /**
   * \brief Creates a RigidBody representing a box.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param mass The mass.
   * \param a    The x extent.
   * \param b    The y extent.
   * \param c    The z extent.
   *
   * \return the rigidbody.
   */
  static RigidBody* createBox(Real mass, Real a, Real b, Real c);  

  /**
   * \brief Adds an external force f to this rigid body in world coordinates.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param position The position.
   * \param f        The f.
   */
  void addExternalForceWCS(const IBDS::Vector3D & position, const IBDS::Vector3D & f);

  /**
   * \brief Adds an external torque in world coordinates. 
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param torque The torque.
   */
  void addExternalTorqueWCS(const IBDS::Vector3D & torque);

  /**
   * \brief Resets the force and torque accumulator.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   */
  void resetForce();

  /**
   * \brief Gets the inertia tensor in object coordinates
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The inertia tensor.
   */
  const IBDS::Matrix3x3 & getInertiaTensor() const;

  /**
   * \brief Sets the inertia tensor.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param inertia The inertia.
   */
  void setInertiaTensor(const IBDS::Matrix3x3 & inertia);

  /**
   * \brief Gets the orientation as a Quarternion.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The orientation.
   */
  const IBDS::Quaternion& getOrientation() const;

  /**
   * \brief Sets the orientation.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param orientation The orientation.
   */
  void setOrientation(const IBDS::Quaternion & R);

  /**
   * \brief Gets the angular velocity.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The angular velocity.
   */
  const IBDS::Vector3D & getAngularVelocity()const;

  /**
   * \brief Sets the angular velocity.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param omega The angular velocity.
   */
  void setAngularVelocity(const IBDS::Vector3D & omega);

  /**
   * \brief Gets the angular acceleration.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The angular acceleration.
   */
  const IBDS::Vector3D & getAngularAcceleration()const;

  /**
   * \brief Sets the angular acceleration.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param omegaDot The angular acceleration.
   */
  void setAngularAcceleration(const IBDS::Vector3D & omegaDot);

};// RigidBody
}// namespace IBDS


#endif