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
* \file src/mbs/integrators/IIntegrator.h
* Declaration of mbslib::IIntegrator
*/
#pragma once

#include <simulation.state/StatefulObject.h>
#include <simulation.integration/ISystemFunction.h>
#include <simulation.integration/Evaluator.h>

namespace nspace{
  /**
  * <summary> Abstract Integrator class.</summary>
  *
  * <remarks> Tobias Becker, 13.04.2012.</remarks>
  */

  class Integrator : public virtual ISimulationObject{
  private:
    Evaluator * _evaluator;
  public:
    // default constructor (no evaluator set)
    Integrator();
    //integrates the evaluator over the interval [a,b]
    virtual void integrate(Real a, Real b)=0;
    // returns the evaluator of this integrator
    inline Evaluator * evaluator(){ return _evaluator; }
    // sets the evaluator of integrator
    void setEvaluator(Evaluator * evaluator);
  protected:
    // evaluates the evaluator at state x ,time t and stepsize h
    inline const StateMatrix & f(const StateMatrix & x, Real t, Real h);
  };



  //implementation
  inline const StateMatrix & Integrator::f(const StateMatrix & x, Real t, Real h){
    if(!evaluator()){
      std::cerr << " No evaluator set.  cannot call f!!"<<std::endl;
      return *reinterpret_cast<StateMatrix*>(0);
    }    
    return evaluator()->f(x,t,h);
  }

}//namespace mbslib
