/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once
#include <simulation.kinematics/KinematicPoint.h>
#include <simulation.dynamics/DynamicBody.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <simulation.kinematics/Velocity.h>
#include <simulation.kinematics/Acceleration.h>
#include <simulation.state/StatefulObject.h>
namespace nspace
{
  /**
   * \brief Particle. A Dynamic Point in Space.  It has 3 Degrees of Freedom
   *        it is governed by the equation \f$ \mathbf{f}_p = m_p \dot \mathbf{\ddot{x}}_p \f$
   *        were \f$p\f$ is the identifier for this particle, \f$m_p\f$ is the particle's mass
   *        \f$\mathbf{f}_p\f$ is the force that is acting on this particle and \f$\mathbf{\ddot{x}}\f$ is the resulting acceleration.
   *
   *        The Particle is a StatefulObject - a state is assignable.
   */
  class Particle : public DynamicBody, public virtual StatefulObject
  {
    TYPED_OBJECT(Particle);
private:
    Vector3D _f;
    Real _m;
    Real * _x;
    Real* _xDot;
    Real * _xDotDot;
public:

    /**
     * \brief The particle's postion \f$\mathbf{x}_p\f$
     */
    Position position;

    /**
     * \brief The velocity \f$\mathbf{\dot{x}}_p\f$.
     */
    LinearVelocity velocity;

    /**
     * \brief The velocity \f$\mathbf{\ddot{x}}_p\f$.
     */
    LinearAcceleration acceleration;

    /**
     * \brief Default constructor.
     *        \f$\mathbf{\ddot{x}}_p=0\f$
     *        \f$\mathbf{\dot{x}}_p=0\f$
     *        \f$\mathbf{x}_p=0\f$
     *        \f$m_p=1\f$
     *
     */
    Particle() : StatefulObject(3,3),_m(0),_x(0),_xDot(0),_xDotDot(0){
      setMass(1);
      _f.setZero();
      position().setZero();
      velocity().setZero();
      acceleration().setZero();
    }
    ~Particle(){}

    static const TypeId type;

    /**
     * \brief Gets body type.
     *
     * \return  The body type.
     */
    const TypeId getBodyType() const {
      return typeof(Particle)->getId();
    }

    /**
     * \brief Gets center of gravity of this particle.
     *
     * \return  The center of gravity.
     */
    const Vector3D &  getCenterOfGravity() const {
      return position();
    };

    /**
     * \brief returns the mass of this particle
     *
     * \return  The mass.
     */
    inline Real getMass() const {
      return _m;
    }

    /**
     * \brief Sets the mass of this particle.
     *
     * \param m The Real to process.
     */
    void setMass(Real m){
      _m = m;
    }

    /**
     * \brief Applies the an impulse to this particle.
     *
     * \param a_wcs The wcs.
     * \param p_wcs The wcs.
     */
    void applyImpulse(const Vector3D& a_wcs, const Vector3D& p_wcs);

    /**
     * \brief Resets the force acting on this particle
     */
    void resetForce();

    /**
     * \brief Adds an external force to the force accumulator of this particle
     *
     * \param f The const Vector3D &amp; to process.
     */
    void addExternalForce(const Vector3D & f);

    /**
     * \brief Adds an external torque - (partcle is left unaltered because of its nature)
     *
     * \param tau The tau.
     */
    void addExternalTorque(const Vector3D & tau){};

    /**
     * \brief Sets the force acting on this partcle
     *
     * \param f The const Vector3D &amp; to process.
     */
    void setForce(const Vector3D & f);

    /**
     * \brief Gets the force. acting on this Particle
     *
     * \return  The force.
     */
    const Vector3D & getForce() const;

    /**
     * \brief Gets the torque acting on this partcile
     *
     * \return  The torque.
     */
    const Vector3D & getTorque() const {
      return Vector3D::Zero();
    }

    /**
     * \brief Calculates the dynamics for this particle - solving the equation \f$ \mathbf{f}_p = m_p \dot \mathbf{\ddot{x}}_p\f$ for \f$\mathbf{\ddot{x}}_p\f$
     */
    void calculateDynamics();

    /**
     * \brief Calculates cached values for this particle (does nothing).
     */
    void calculateCachedValues(){};

    /**
     * \brief Calculates the K matrix.
     *
     * \param [out]  K \f$\mathit{K}_p \in  \mathbb{R}^{3 \times 3} \f$
     * \param a_wcs       The world coordinates of point a.
     * \param b_wcs       The world coordinates of point b.
     */
    void calculateK(Matrix3x3& K, const Vector3D & a_wcs, const Vector3D & b_wcs) const;

    /**
     * \brief Executes the state assigned action. this is called every time that the underlying state object changes
     */
    void onStateAssigned(){
      _x=state().stateVector(0);
      _xDot=state().stateVector(1);
      _xDotDot=state().stateVector(2);
    };

    /**
     * \brief Notifies that the state changed has changed (ie when integrating loading a state snapshot).
     */
    void notifyStateChanged();

    /**
     * \brief Notifies that the current state is needed. the particle must calculate the dynamics equations
     */
    void notifyStateNeeded();
  };
}
