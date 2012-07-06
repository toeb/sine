#pragma once

#include <Math/Matrix3x3.h>
#include <Math/Quaternion.h>
#include <Simulation/Integration/IIntegrable.h>
#include <Simulation/Core/ISimulationObject.h>
#include <Math/Vector3D.h>
#include <Simulation/Kinematics/CoordinateSystem.h>

#include <Simulation/Kinematics/Acceleration.h>
#include <Simulation/Kinematics/Velocity.h>
#include <Simulation/Kinematics/AngularAcceleration.h>
#include <Simulation/Kinematics/AngularVelocity.h>

namespace IBDS{


/**
 * \brief Kinematic body class.  
 * 				Describes a kinematic Body.  
 * 				 
 * 				 is a  coordinate system extended by the first two derivatives of the position and oirientation
 *
 * \author Tobias Becker
 * \date 10.04.2012
 */
class KinematicBody : public IIntegrable, public virtual CoordinateSystem{
public:

  LinearVelocity velocity;
  LinearAcceleration acceleration;
  AngularVelocity angularVelocity;
  AngularAcceleration angularAcceleration;

  void setZero();
  void setMovementToZero();
    KinematicBody();
  ~KinematicBody();


  
  /** Members of IIntegrable
  */
  void getDerivedState(Real * xDot)const;
  void setState(const Real * state);
  void getState(Real * state)const;
  int getStateDimension()const;
};
}// namespace IBDS