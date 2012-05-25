#pragma once

#include <Simulation/Dynamics/DynamicBody.h>
#include <Simulation/Kinematics/KinematicBody.h>

namespace IBDS{
/**
 * \brief Rigid body class.  
 * 				Describes a Rigid Body.  Is an extension of Particle
 * 				 
 *
 * \author Tobias Becker
 * \date 10.04.2012
 */
class RigidBody : public virtual DynamicBody,public virtual KinematicBody {
private:  
  Real _m;
  ///< The inertia tensor
  Matrix3x3 _J;
  ///< The inverse inertia tensor in object coordinates
  Matrix3x3 _J_inv_ocs;
  ///< The inverse inertia tensor in world coordinates
  Matrix3x3 _J_inv_wcs;  

  ///< The force accumulator
  Vector3D _f;
  ///< The torque accumulator
  Vector3D _tau;


public:

  RigidBody();
  ~RigidBody();

  
  const Vector3D &  getCenterOfGravity()const {return getPosition();};

  void calculateDynamics();
  void calculateCachedValues();
  Real getMass()const{return _m;}
  void setMass(Real m){_m = m;}

  void addExternalForce(const IBDS::Vector3D & f);
  void addExternalForce(const IBDS::Vector3D & position, const IBDS::Vector3D & f);
  void addExternalTorque(const IBDS::Vector3D & torque);

  const Vector3D & getTorque()const;
  const Vector3D & getForce()const;

  void resetForce();
  
  void setInertiaTensor(const IBDS::Matrix3x3 & inertia);
  const Matrix3x3 & getInertiaTensor() const;

  const Matrix3x3 & getInvertedInertiaTensor() const;
  void calculateInvertedInertiaTensor();
  
  const Matrix3x3 & getInvertedInertiaTensorInWorldCoordinates()const;
  void calculateInvertedInertiaTensorInWorldCoordinates();
  

  void applyImpulse(const Vector3D & a_wcs, const Vector3D& p_wcs);
 
  void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const; 

};// RigidBody
}// namespace IBDS