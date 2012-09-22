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
 * \file src/mbs/integrators/implementations/ImplicitEuler.h
 * Declaration of mbslib::ImplicitEulerIntegrator
 */
#pragma once
#include <simulation.integration/StepIntegrator.h>
namespace nspace{

/**
 * \brief Implicit euler integrator. (uses fixpoint iteration to solve the implicit equation)
 */
class ImplicitEuler : public StepIntegrator{
private:
  StateMatrix _x_next;
  TScalar _tolerance;
  int _maxIterations;
public:

  ImplicitEuler(Real h=0.01, Real tolerance = 10e-5,int maxIterations=100);

  void doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h);
  
  int getErrorOrder()const;
protected:
  void logParameters(std::ostream & out);
};//class ImplicitEuler
}//namespace mbslib

