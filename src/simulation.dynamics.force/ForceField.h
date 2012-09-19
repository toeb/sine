#pragma once

#include <simulation.dynamics.force/Force.h>
#include <common/Time.h>
#include <algorithm>
#include <functional>

namespace nspace{
  class ForceField : public virtual Force{
  TYPED_OBJECT;
  private:
    std::function<void (Vector3D &, Vector3D & ,const  Vector3D& , Time)> _f;
  public:
    ForceField(std::function<void (Vector3D &, Vector3D & , const  Vector3D& , Time)> f):_f(f){

    }
    void act( std::vector<DynamicBody*> & targets, Real time ){
      std::for_each(targets.begin(), targets.end(), [this,time](DynamicBody * target){
        const Vector3D & cog = target->getCenterOfGravity();
        Vector3D force;
        Vector3D torque;
        _f(force,torque, cog,time);
        target->addExternalForce(force);
        target->addExternalTorque(torque);
      
      });


    }
  
  };

}
