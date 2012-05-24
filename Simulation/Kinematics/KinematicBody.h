#pragma once

#include <Math/Matrix3x3.h>
#include <Math/Quaternion.h>
#include <Simulation/Integrators/IIntegrable.h>
#include <Simulation/Core/ISimulationObject.h>
#include <Math/Vector3D.h>
#include <Simulation/Geometry/CoordinateSystem.h>

namespace IBDS{
/**
 * \brief Rigid body class.  
 * 				Describes a Rigid Body.  Is an extension of Particle
 * 				 
 *
 * \author Tobias Becker
 * \date 10.04.2012
 */
class KinematicBody : public virtual IIntegrable, public virtual CoordinateSystem{
protected:
  ///< The velocity in World Coordinatees
  Vector3D _v;
  ///< The acceleration
  Vector3D _a;
  ///< The angular velocity
  Vector3D _omega;
  ///< The angular acceleration
  Vector3D _omegaDot;
public:
  void setZero();
  void setMovementToZero();

  KinematicBody();
  ~KinematicBody();
  
  /** Members of IIntegrable
  */
  void getDerivedState(Real * xDot)const;
  void evaluate();
  void setState(const Real * state);
  void getState(Real * state)const;
  int getStateDimension()const;

  const Vector3D & getAngularVelocity()const;
  void setAngularVelocity(const Vector3D & omega);
  void addAngularVelocity(const Vector3D & omega);
  
  const Vector3D & getAngularAcceleration()const;
  void setAngularAcceleration(const Vector3D & omegaDot);
    
  const  Vector3D  &  getVelocity()const;
  void setVelocity(const Vector3D & velocity);
  void addVelocity(const Vector3D & velocity);

  const Vector3D & getAcceleration()const;
  void setAcceleration(const Vector3D & acceleration);

protected:
};
}// namespace IBDS