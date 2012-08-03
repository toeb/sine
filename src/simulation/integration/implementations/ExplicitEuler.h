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
 * \file src/mbs/integrators/implementations/ExplicitEuler.h
 * Declaration of mbslib::ExplicitEuler
 */
#pragma once
#include <simulation/integration/StepIntegrator.h>

namespace nspace {

/**
 * \brief The explicit Euler integrator does the simple integration  x[i+1] = x[i]+h*xDot in every timestep.
 */
class ExplicitEuler : public StepIntegrator{
public:

  /**
   * \brief Constructor.
   *
   * \param [in]  system   The system.
   * \param stepSize          (optional) size of the step (default is 0.01).
   */
  ExplicitEuler(Real h0 = 0.01):StepIntegrator(h0){
    this->setName("ExplicitEuler");
  };

  /**
   * \brief does a explicit Euler step.
   *
   * \param t_i The current time t_i.
   * \param h   The timestep length h.
   *
   * \return  .
   */
 void doStep(Real t_i,  Real h){
    x = x + h * f(t_i, x,h);
 };

  int getErrorOrder()const{return 2;}
};//class ExplicitEulerIntegrator
}//namespace mbslib;

