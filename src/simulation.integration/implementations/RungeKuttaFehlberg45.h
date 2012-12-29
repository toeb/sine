/*
* Copyright (C) 2011
* Simulation, Systems Optimization and Robotics Group (SIM)
* Technische Universitaet Darmstadt
* Hochschulstr. 10
* 64289 Darmstadt, Germany
* www.sim.tu-darmstadt.de
*
* This file is part of the mbslib.
* All rights are reserved by the copyright holder.
*
* The mbslib is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* You may use the mbslib or parts of it only with the written permission of the copyright holder.
* You may NOT modify or redistribute any part of the mbslib without the prior written
* permission by the copyright holder.
*
* Any violation of the rights and restrictions mentioned above will be prosecuted by civil and penal law.
* Any expenses associated with the prosecution will be charged against the violator.
*/

/**
* \file src/mbs/integrators/implementations/RungeKuttaFehlberg45.h
* Declaration of mbslib::RungeKuttaFehlberg45
*/
#pragma once

#include <simulation.integration/StepIntegrator.h>

namespace nspace{
  /**
  * \brief Runge Kutta Fehlberg 45.
  * 				algorihm taken from:
  * 				http://math.fullerton.edu/mathews/n2003/rungekuttafehlberg/RungeKuttaFehlbergProof.pdf
  * 				modified stepsize calculation as seen in the script "gewoehnliche numerische differentialgleichungen" by prof. Kiehl tu darmstadt
  */
  class RungeKuttaFehlberg45 : public StepIntegrator{
  private:
    ///< The tolerance
    Real tolerance;
    /// <summary> alpha in (0,1] default 0.9 (reduction of new step size) </summary>
    Real alpha;
    /// <summary> beta in (0,1) default 0.5 lower bound of new step size h_new >= beta*h_old </summary>
    Real beta;
    ///< gamma in (1,infinity) default 1.5 upper bound of new step size h_new <= gamma * h_old
    Real gamma;
    Real maximumStepSize;
    Real minimumStepSize;
    Real currentErrorEstimate;
    StateMatrix k1,k2,k3,k4,k5,k6,y,z;
  public:

    /**
    * \brief Constructor.
    *
    * \param tolerance       (optional) the tolerance used by RKF45 .
    * \param initialStepSize (optional) size of the initial step.
    * \param alpha           (optional) alpha in (1,1] - stepsize reduction factor in every step default should be 0.9.
    * \param beta            (optional) beta in [0,1] - the maximum decrease factor from step h_i to h_{i+1}.
    * \param gamma           (optional) gamma in [1, inf) - the maximum increase factor from step h_i to h_{i+1}
    * \param maxStepSize     (optional) the maximum step size h_i <= maxStepSize for all i in N.
    * \param minStepSize     (optional) the minimum step size h_i >= minStepSize for all i in N.
    */
    RungeKuttaFehlberg45(
      Real tolerance = 10e-5,
      Real h0=10e-3,
      Real alpha=0.9,
      Real beta=0.5,
      Real gamma=1.5,
      Real maxStepSize = 1,
      Real minStepSize = 10e-7
      );

    /**
    * \brief Sets a tolerance.
    *
    * \param tolerance The tolerance.
    */
    void setTolerance(const Real tolerance);

    /**
    * \brief Gets the tolerance.
    *
    * \return  The tolerance.
    */
    Real getTolerance();

    /**
    * \brief Gets the error order. which is 5 in case of the rkf45 algorithm
    *
    * \return  The error order.
    */
    int getErrorOrder()const;

    const Real& getErrorEstimate()const;
  protected:
    void logParameters(std::ostream & o)const;

    void doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h);
  private:
    void calculateRungeKutta45(Real t_i, const StateMatrix & x_i,  Real h, StateMatrix & rk4, StateMatrix & rk5);
  };//class RungeKuttaFehlberg45
}//namespace mbslib
