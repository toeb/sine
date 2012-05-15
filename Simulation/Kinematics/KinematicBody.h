#pragma once

#include <Math/Matrix3x3.h>
#include <Math/Quaternion.h>
#include <Simulation/Integrators/IIntegrable.h>
#include <Simulation/ISimulationObject.h>
#include <Math/Vector3D.h>

#include <Simulation/SimulationObjects/Body.h>

namespace IBDS{
/**
 * \brief Rigid body class.  
 * 				Describes a Rigid Body.  Is an extension of Particle
 * 				 
 *
 * \author Tobias Becker
 * \date 10.04.2012
 */
class KinematicBody{
private:
  Matrix3x3 _R;
  Matrix3x3 _RT;  

  ///< The orientation
  Quaternion _q;
  ///< The position in World Coordinates
  Vector3D _x;
  ///< The velocity in World Coordinatees
  Vector3D _xDot;
  ///< The acceleration
  Vector3D _xDotDot;
  ///< The angular velocity
  Vector3D _omega;
  ///< The angular acceleration
  Vector3D _omegaDot;


public:
  KinematicBody();
  ~KinematicBody();
  
  /** Members of IIntegrable
  */
  void getDerivedState(Real * xDot)const;
  void evaluate();
  void setState(const Real * state);
  void getState(Real * state)const;
  int getStateDimension()const;
 
  void worldToObjectCoordinates(const Vector3D & r_wcs, Vector3D & r_ocs)const;
  void objectToWorldCoordinates(const Vector3D & r_ocs, Vector3D & r_wcs)const;

  const Matrix3x3 & getRotationMatrix()const;
  const Matrix3x3 & getTransposedRotationMatrix()const;
  void calculateRotationMatrices();

  const  Quaternion  &  getOrientation() const;
  void setOrientation(const IBDS::Quaternion & R);

  const Vector3D & getAngularVelocity()const;
  void setAngularVelocity(const Vector3D & omega);

  const Vector3D & getAngularAcceleration()const;
  void setAngularAcceleration(const Vector3D & omegaDot);


  const  Vector3D  &  getPosition()const;
  void setPosition(const Vector3D & position);
  
  const  Vector3D  &  getVelocity()const;
  void setVelocity(const Vector3D & velocity);

  const Vector3D & getAcceleration()const;
  void setAcceleration(const Vector3D & acceleration);
};
}// namespace IBDS