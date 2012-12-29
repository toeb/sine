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
* \file src/mbs/integrators/implementations/AdamsMoulton4.h
* Declaration of mbslib::AdamsMoulton4
*/
#pragma once
#include <simulation.integration/StepIntegrator.h>

namespace nspace{
#define ADAMS_MOULTON_HISTORY_COUNT 9
  /**
  * \brief AdamsMoulton4 integrator.
  */
  class AdamsMoulton4 : public StepIntegrator{
  private:
    StateMatrix f_i;
    StateMatrix f_1;
    StateMatrix f_2;
    StateMatrix f_3;
    StateMatrix f_4;
    StateMatrix f_5;
    StateMatrix f_6;
    StateMatrix f_7;
    StateMatrix f_8;

  public:
    AdamsMoulton4(Real h=0.01);
  protected:
    void doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h);
  private:
    void updateHistory();
    void halveStepSize();
    void doubleStepSize();
    StateMatrix initialStep(TTime t_i, const StateMatrix & x_i, TTime h);
  };//class ImplicitEulerIntegrator
}//namespace mbslib
