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

#pragma once

#include <ostream>
#include <simulation/integration/Integrator.h>
namespace nspace{
  
class StepIntegrator : public Integrator{
private:
  ///< a - the lower bound
  Time _a;
  ///< b - the upper bound
  Time _b;
  ///< The integration variable t
  Time _t;
  ///< The current step size h(t)
  Time _h;
  ///< The initial step size
  Time _h0;
protected:
  /**
   * <summary> Executes an integration step.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   */
  virtual void  doStep(Real t_i, Real h)=0;
  

  /**
   * \brief Accessor for the initial step size h0
   *
   * \return .
   */
  inline const Real & h0()const{return _h0;};
public:
  /**
   * \brief Allows access to the step size
   *
   * \return .
   */
  inline Real & h(){return _h;};
  inline bool needsIntegration(){
    // if the integrator has reached not reached the upper bound 
    return _t+_h < _b;
  }

  /**
   * \brief access to the current time.
   *
   * \return .
   */
  inline const Time & t(){return _t;}
  
  inline void setLowerBound(Time start){
    _a= start;
    if(_t < _a)_t=_a;
    if(_a <= _b)return;
    std::cerr<< "StepIntegrator::setLowerBound: attempt to set lower bound higher than upper bound"<<std::endl;
    _a = _b;
  }
  inline void setUpperBound(Time target){
    _b= target;
    if(_t > _b) _t = _b;
    if(_b >= _a)return;
    std::cerr<< "StepIntegrator::setLowerBound: attempt to set upperb ound lower than lower bound"<<std::endl;
    _b = _a;
  }

  inline const Time & lowerBound()const{return _a;}
  inline const Time & upperBound()const{return _b;}

  Time step(){
    if(!needsIntegration())return _t;  
    loadState(_t);
    doStep(_t,_h);
    _t += _h;
    storeState(_t);
    return _t;
  }

  Time integrate(){
    while(needsIntegration())step();
    return t();
  }
  
  
  StepIntegrator(Real h0=0.01):_h(h0),_h0(h0),_a(0.0),_b(0.0),_t(0.0){

  }

   
protected:

  //void log(const VectorND & x_i,  TTime t, TTime h, int step)const;
  virtual void logParameters(std::ostream & o)const;
  /**
   * <summary> Integrates.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="initialValue"> The initial value.</param>
   * <param name="a">            a.</param>
   * <param name="b">            The b.</param>
   *
   * <returns> .</returns>
   */
  void doIntegration(Real a, Real b);

};

}