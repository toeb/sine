#pragma once


#include <simulation.state/StatefulObject.h>
#include <simulation/ISimulationObject.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <simulation.kinematics/Acceleration.h>
#include <simulation.kinematics/Velocity.h>
#include <simulation.kinematics/AngularAcceleration.h>
#include <simulation.kinematics/AngularVelocity.h>

namespace nspace{


/**
 * \brief Kinematic body class.  
 * 				Describes a kinematic Body.  
 * 				 
 * 				 is a  coordinate system extended by the first two derivatives of the position and oirientation
 *
 * \author Tobias Becker
 * \date 10.04.2012
 */
class KinematicBody : public StatefulObject, public virtual CoordinateSystem{
public:

  LinearVelocity velocity;
  LinearAcceleration acceleration;
  AngularVelocity angularVelocity;
  AngularAcceleration angularAcceleration;

  void setZero();
  void setMovementToZero();
  KinematicBody();
  ~KinematicBody();

  void notifyStateNeeded();
  void notifyStateChanged();
  
  
};
}