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
 * \file src/mbs/integrators/implementations/AdamsBashford4.h
 * Declaration of mbslib::AdamsBashford4
 */
#pragma once
#include <integration/SingleStepIntegrator.h>

namespace mbslib{

/**
 * \brief AdamsBashford 4th Order integrator.
 */
class AdamsBashford4 : public StepIntegrator{
private:
  ///< The History values
  StateMatrix f_1;
  StateMatrix f_2;
  StateMatrix f_3;
public:

  /**
   * \brief Constructor. Initializes the history to f(0,x_0)
   *
   * \param [in]  system  The system.
   * \param initialStepSize   (optional) size of the initial step.
   */
  AdamsBashford4(Real h0 = 0.01) : StepIntegrator(h0){
    setName("Adams Bashforth 4");
  };
  /**
   * \brief Steps the integrator.  Adams Bashford 4th order step as described in http://www.icp.uni-
   *        stuttgart.de/~hilfer/lehre/100-online/skriptum/html_book00/node104.html.
   *
   * \param t_i The time t_i.
   * \param x_i The state of the system at time t_i
   * \param h   The timestep length h.
   *
   * \return  .
   */  
  void doStep(Real t_i,  Real h){
    //evaluate the function at t_i, x_i
    StateMatrix f_0 = f(t_i, x,h);
    //calculate the new approximation
    x = x + h/24*(55.0*f_0 - 59.0*f_1+ 37.0*f_2-9.0*f_3);
    // store history
    f_3 = f_2;
    f_2 = f_1;
    f_1 = f_0;    
  };
  
  int getErrorOrder()const{return 1;}
  void initializeIntegrator(const StateMatrix & currentState){
    StateMatrix f_0 = f(0,currentState,h());
    f_1=f_2=f_3 = f_0;
  }

};//class AdamsBashford4
}//namespace mbslib
