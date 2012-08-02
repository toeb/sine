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
class RigidBody : public DynamicBody, public virtual IIntegrable {
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
  

  ///< The kinematic body
  KinematicBody _kinematics;
public:

  inline CoordinateSystem & coordinates(){return kinematics();}
  inline const CoordinateSystem & coordinates()const {return kinematics();}

  inline KinematicBody & kinematics(){return _kinematics;};
  inline const KinematicBody & kinematics()const{return _kinematics;};

  RigidBody(Real mass):_m(mass){

  }

  RigidBody(Real mass, const Matrix3x3 inertia):_m(mass){
    setInertiaTensor(inertia);
  }

  RigidBody();

  ~RigidBody();

  static const TypeId type;
  const TypeId getBodyType()const;
  
  const Vector3D &  getCenterOfGravity()const {return kinematics().position();};

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


  //integragble impl.
  void getDerivedState(Real * xDot)const;
  void setState(const Real * state);
  void getState(Real * state)const;
  int getStateDimension()const;

};// RigidBody
}// namespace IBDS