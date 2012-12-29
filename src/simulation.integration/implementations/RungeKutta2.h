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
* \file src/mbs/integrators/implementations/RungeKutta2.h
* Declaration of mbslib::RungeKutta2
*/
#pragma once
#include <simulation.integration/StepIntegrator.h>
namespace mbslib{
  /**
  * \brief Runge Kutta integrator of order 2.
  */
  class RungeKutta2 : public StepIntegrator{
  private:
    StateMatrix k1,k2;
  public:

    /**
    * \brief Constructor. Initialises this Runge Kutta integrator. the default step size is 0.02 s
    *
    * \param [in]  system  The system.
    * \param stepSize          (optional) size of the step.
    */
    RungeKutta2(Real h0 =0.02):StepIntegrator(h0){
      this->setName("RungeKutta2");
    };

    /**
    * \brief  Does a Runge Kutta 2 step as explained in
    *         http://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods.
    *
    * \param  t_i The time t_i.
    * \param  x_i The system state x at time t_i
    * \param  h   The timestep length h.
    *
    * \return .
    */

    void doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h){
      k1 = h * f(x_i,t_i,h);
      k2 = h * f(x_i+0.5*k1,t_i+0.5*h,h);
      x_next = x_i + k2;
    };

    int getErrorOrder()const{
      return 2;
    }
  };//class Second OrderRungeKuttaIntegrator
}//namespace mbslib
