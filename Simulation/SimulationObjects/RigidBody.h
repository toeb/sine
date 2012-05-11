#pragma once

#include <Math/Matrix3x3.h>
#include <Math/Quaternion.h>
#include <Simulation/Integrators/IIntegrable.h>
#include <Simulation/ISimulationObject.h>
#include <Math/Vector3D.h>
#include "Body.h"

namespace IBDS{
/**
 * \brief Rigid body class.  
 * 				Describes a Rigid Body.  Is an extension of Particle
 * 				 
 *
 * \author Tobias Becker
 * \date 10.04.2012
 */
class RigidBody : public Body {
private:
  
  ///< The inertia tensor
  Matrix3x3 _J;
  ///< The inverse inertia tensor in object coordinates
  Matrix3x3 _J_inv_ocs;
  ///< The inverse inertia tensor in world coordinates
  Matrix3x3 _J_inv_wcs;  
  Matrix3x3 _R;
  Matrix3x3 _RT;  

  ///< The mass
  Real _m;
  ///< The orientation
  Quaternion _q;
  ///< The position in World Coordinates
  Vector3D _x;
  ///< The velocity in World Coordinatees
  Vector3D _xDot;
  ///< The angular velocity
  Vector3D _omega;
  ///< The angular acceleration
  Vector3D _omegaDot;
  ///< The force accumulator
  Vector3D _f;
  ///< The torque accumulator
  Vector3D _tau;

public:
  RigidBody();
  ~RigidBody();
  
  /** Members of IIntegrable
  */
  void getDerivedState(Real * xDot)const;
  void evaluate();
  void setState(const Real * state);
  void getState(Real * state)const;
  int getStateDimension()const;
  
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
   * \brief Converts r (in world coordinates) to object coordinates.
   *
   * \author Tobi
   * \date 09.05.2012
   *
   * \param r_wcs The wcs.
   *
   * \return .
   */
  void worldToObjectCoordinates(const Vector3D & r_wcs, Vector3D & r_ocs)const;

  /**
   * \brief Converts r (in object coordinates) to world coordinates.
   *
   * \author Tobi
   * \date 10.05.2012
   *
   * \param r_ocs The ocs.
   *
   * \return .
   */
  void objectToWorldCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs)const;

  /**
   * \brief Adds an external force f to this rigid body in world coordinates.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param position The position.
   * \param f        The f.
   */
  void addExternalForce(const IBDS::Vector3D & position, const IBDS::Vector3D & f);

  /**
   * \brief Adds an external force to the center of gravity. 
   *
   * \author Tobi
   * \date 10.05.2012
   *
   * \param f The f.
   */
  void addExternalForce(const IBDS::Vector3D & f);

  /**
   * \brief Adds an external torque in world coordinates. 
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param torque The torque.
   */
  void addExternalTorque(const IBDS::Vector3D & torque);

  /**
   * \brief Resets the force and torque accumulator.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   */
  void resetForce();


  const Matrix3x3 & getRotationMatrix()const;
  const Matrix3x3 & getTransposedRotationMatrix()const;
  void calculateRotationMatrices();
  /**
   * \brief Gets the force acting on this body.
   *
   * \author Tobias Becker
   * \date 16.04.2012
   *
   * \return The force.
   */
  const Vector3D & getForce()const;

  /**
   * \brief Gets the torque currently acting on the body.
   *
   * \author Tobi
   * \date 10.05.2012
   *
   * \return The torque.
   */
  const Vector3D & getTorque()const;

  /**
   * \brief Gets the mass.
   *
   * \author Tobias Becker
   * \date 16.04.2012
   *
   * \return The mass.
   */
  Real getMass()const ;
  

  /**
   * \brief Sets the inertia tensor.
   * calulates the inverted inertia tensor
   * 
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \param inertia The inertia.
   */
  void setInertiaTensor(const IBDS::Matrix3x3 & inertia);
  /**
   * \brief Sets the mass.
   *
   * \author Tobias Becker
   * \date 16.04.2012
   *
   * \param mass The mass.
   */
  void setMass(Real mass);

  /**
   * \brief Gets the inertia tensor in object coordinates
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The inertia tensor.
   */
  const Matrix3x3 & getInertiaTensor() const;

  /**
   * \brief Gets the inverted inertia tensor in object coordinates.
   *
   * \return  The inverted inertia tensor.
   */
  const Matrix3x3 & getInvertedInertiaTensor() const;
  void calculateInvertedInertiaTensor();
  /**
   * \brief Gets the inverted inertia tensor in world coordinates.
   *
   * \author Tobi
   * \date 10.05.2012
   *
   * \return The inverted inertia tensor in world coordinates.
   */
  const Matrix3x3 & getInvertedInertiaTensorInWorldCoordinates()const;
  void calculateInvertedInertiaTensorInWorldCoordinates();

  /**
   * \brief Gets the orientation as a Quarternion.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The orientation.
   */
 const  Quaternion  &  getOrientation() const;

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
   * \brief Applies an impulse p at point a.
   *
   * \author Tobi
   * \date 10.05.2012
   *
   * \param a_wcs the point a in world coordinates.
   * \param p_wcs the impulse p in world coordinates
   */
  void applyImpulse(const Vector3D & a_wcs, const Vector3D& p_wcs);
 

  const  Vector3D  &  getPosition()const;
  void setPosition(const Vector3D & position);
  const  Vector3D  &  getVelocity()const;
  void setVelocity(const Vector3D & velocity);

   /**
   * \brief Gets the angular velocity.
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The angular velocity.
   */
  const Vector3D & getAngularVelocity()const;

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
   * \brief Gets the angular acceleration. (evaluates the equations)
   *
   * \author Tobias Becker
   * \date 10.04.2012
   *
   * \return The angular acceleration.
   */
  const Vector3D & getAngularAcceleration()const;

  void calculateAngularAcceleration();

  /**
  * \brief Calculates the K matrix.
  *
  * \author Tobi
  * \date 10.05.2012
  *
  * \param s_wcs The center of gravity of the body.
  * \param a_wcs The point a.
  * \param b_wcs The point b.
  *
  * \return The calculated k.
  */
  void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const; 

};// RigidBody
}// namespace IBDS