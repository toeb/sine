#pragma once

#include <ostream>
#include <simulation.integration/Integrator.h>
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

    StateMatrix x_next;
  protected:
    /**
    * <summary> Executes an integration step.</summary>
    */
    virtual void  doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h)=0;

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
      const StateMatrix & x = evaluator()->x();
      if(x.size()){
        //x_next.resize(x.rows(),x.cols(),false);
        x_next.resize(x.rows(),x.cols());
        x_next.setZero();
        doStep(x_next, evaluator()->x(),_t,_h);
        evaluator()->setX(x_next);
      }
      _t += _h;
      return _t;
    }

    Time integrate(){
      while(needsIntegration())step();
      return t();
    }


    StepIntegrator(Real h0=0.01):_h(h0),_h0(h0),_a(0.0),_b(REAL_MAX),_t(0.0){

    }


  protected:

    void integrate(Real a, Real b);

  };

}