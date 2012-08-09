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

#include <simulation/integration/IStatefulObject.h>
#include <simulation/integration/ISystemFunction.h>
#include <simulation/timing/Timeable.h>

namespace nspace{
  /**
 * <summary> Abstract Integrator class.</summary>
 *
 * <remarks> Tobias Becker, 13.04.2012.</remarks>
 */
class Integrator : public Timeable{
private:
  /// <summary> The integrable </summary>
  IStatefulObject * _statefulObject;
  ISystemFunction * _systemFunction;
  
  int _dimension;

  StateMatrix _derivedState;

  long _evaluationCount;
  std::ostream * _log;

protected:
  virtual void doIntegration(Real a, Real b)=0;

  inline void loadState(Real t){
    if(!_statefulObject)return;
		State state(x);
		_statefulObject->resizeState(state);
    _statefulObject->exportState(state);
  }
  inline void storeState(Real t){
    if(!_statefulObject)return;   
    _statefulObject->importState(State(x));
  }
public:
  /**
   * \brief allows access to the state
   * 				subclasses use this to set the integrated state.
   *
   * \return .
   */
  
  StateMatrix x;

  Integrator();


  /**
   * \brief Integrates the stateful object over the interval [a,b]. the initial value is managed
   *        by the integrable.
   *
   * \param a beginning of the interval.
   * \param b end of the interval.
   * 					
   */
  void integrate(Real a, Real b);
  
  IStatefulObject * statefulObject();
  void setStatefulObject(IStatefulObject * stateful);
  void setSystemFunction(ISystemFunction * systemFunction);
  ISystemFunction * getSystemFunction();  


  void setLog(std::ostream * logStream){_log = logStream;}
  std::ostream * getLog()const{return _log;}


  
  //metadata functions
  //returns a value between zero and one depending on the progress
  virtual Real progress()const {return 0;};
  virtual Real getErrorEstimation()const{return -1;}  
  virtual int getErrorOrder()const{return 0;} 
  long getEvaluationCount()const;   
  void resetEvaluationCount(); 
  virtual void logIntegratorInfo(std::ostream & o)const;
  virtual void logParameters(std::ostream & o)const{  }

protected:

  /**
   * \brief evaluates the function at state x.
   *
   * \param t The integration variable.
   * \param x The state.
   * \param h The timestep size.
   */
  const StateMatrix & f(Real t, const StateMatrix & x, Real h);
};


}//namespace mbslib
