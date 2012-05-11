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

#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "Common/Config.h"
#include "Math/Vector3D.h"
#include "Simulation/Integrators/IIntegrable.h"
#include "SImulation/ISimulationObject.h"
#include "Body.h"
#include "Visualization/MiniGL.h"
#include <Visualization/IRenderer.h>
namespace IBDS
{
class Particle : public Body, public IRenderer
  {
  private:
    Real _mass;
    Vector3D _position;
    Vector3D _velocity;
    Vector3D _acceleration;
    Vector3D _f;
  public:
    Particle ();
    ~Particle ();
    void applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs);
    
    void getDerivedState(Real * xDot)const;
    void evaluate();
    void setState(const Real * state);
    void getState(Real * state)const;
    int getStateDimension()const;

    void resetForce();
    void addExternalForce(const Vector3D & f);
    void setForce(const Vector3D & f);
    const Vector3D & getForce()const;

    Real getMass() const;
    void setMass(const Real & val);
    const  Vector3D  & getPosition() const;
    void setPosition(const Vector3D & val);
    const  Vector3D  &   getVelocity() const;
    void setVelocity(const Vector3D & val);

    void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs)const;

  };
}

#endif
