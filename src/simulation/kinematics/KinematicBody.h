#pragma once


#include <simulation/integration/IStatefulObject.h>
#include <simulation/core/ISimulationObject.h>
#include <simulation/kinematics/CoordinateSystem.h>
#include <simulation/kinematics/Acceleration.h>
#include <simulation/kinematics/Velocity.h>
#include <simulation/kinematics/AngularAcceleration.h>
#include <simulation/kinematics/AngularVelocity.h>

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
class KinematicBody : public IStatefulObject, public virtual CoordinateSystem{
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
  void exportDerivedState(IState & xDot)const;
  void importState(const IState & state);
  void exportState(IState & state)const;
  unsigned int stateDimension()const;
  unsigned int availableDerivatives()const;
};
}