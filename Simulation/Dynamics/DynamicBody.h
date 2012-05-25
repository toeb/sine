#pragma once
#include "Simulation/Core/ISimulationObject.h"
#include <Simulation/Integrators/IIntegrable.h>
#include <Math/Vector3D.h>
namespace IBDS {
class DynamicBody : public virtual IIntegrable{
  public:     
    virtual void calculateDynamics()=0;
    virtual void calculateCachedValues()=0;
    
    virtual Real getMass()const=0;
    virtual void setMass(Real m)=0;
    
    virtual const Vector3D & getCenterOfGravity()const=0;
    

	  virtual void resetForce() = 0;
    virtual void addExternalForce(const Vector3D & f) = 0;
    virtual void addExternalTorque(const Vector3D & tau)=0;
    virtual const Vector3D & getTorque()const =0;
    virtual const Vector3D & getForce()const=0;

    virtual void applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs)=0;   
    virtual void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const=0;
    
    bool isFixed()const;

  };
}