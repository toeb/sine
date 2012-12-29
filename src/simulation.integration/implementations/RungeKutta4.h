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
* \file src/mbs/integrators/implementations/RungeKutta4.h
* Declaration of mbslib::RungeKutta4
*/
#pragma once
#include <simulation.integration/StepIntegrator.h>
namespace nspace{
  class RungeKutta4 : public StepIntegrator{
  private:
    StateMatrix k1;
    StateMatrix k2;
    StateMatrix k3;
    StateMatrix k4;

  public:

    RungeKutta4(Real h0);
    /**
    * \brief Executes a fourth order Runge Kutta step as described in http://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods.
    *
    * \param t_i The time t_i.
    * \param x_i The system state at time t_i
    * \param h   The timestep length h.
    *
    * \return the new system state t_i+1 .
    */
    void doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h);

    int getErrorOrder()const;
    void logParameters(std::ostream & o)const;
  };//class RungeKutta4
}//namespace mbslib;
