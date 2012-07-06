/*
 * IBDS - Impulse-Based Dynamic Simulation Library
 * Copyright (c) 2003-2008 Jan Bender http://www.impulse-based.de
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Jan Bender - Jan.Bender@impulse-based.de
 */
#pragma once

#include <Simulation/Dynamics/DynamicBody.h>
#include <Simulation/Kinematics/CoordinateSystem.h>
#include <Simulation/Kinematics/Velocity.h>
#include <Simulation/Kinematics/Acceleration.h>
namespace IBDS
{
class Particle : public DynamicBody, public virtual IIntegrable
  {  
  private:
    Vector3D _f;
    Real _m;
  public:
    //value holders to kinematic properties
    Position position;
    LinearVelocity velocity;
    LinearAcceleration acceleration;

    Particle(){
      setMass(1);
      position().setZero();
      velocity().setZero();
      acceleration().setZero();
    }
    ~Particle(){
    }

    static const TypeId type;
    const TypeId getBodyType()const;


   
    const Vector3D &  getCenterOfGravity()const {return position();};

    Real getMass()const{return _m;}
    void setMass(Real m){_m = m;}

    void applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs);
    
    void getDerivedState(Real * xDot)const;
    void setState(const Real * state);
    void getState(Real * state)const;
    int getStateDimension()const;

    void resetForce();
    void addExternalForce(const Vector3D & f);
    void addExternalTorque(const Vector3D & tau){};
    void setForce(const Vector3D & f);

    const Vector3D & getForce()const;
    const Vector3D & getTorque()const{return Vector3D::Zero();}
    
    void calculateDynamics();

    void calculateCachedValues(){};

  
    void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const;

  };
}
