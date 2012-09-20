#pragma once
#include <config.h>
namespace nspace{

class AverageRate : public IAverage{
  private:
    bool _initialized;
    Time _lastSampleTime;
    IAverage & _average;
    Real _lastSample;
  public:
    AverageRate(IAverage & average):_average(average),_initialized(false){

    }
    void addSample( Real sample ){
      if(!_initialized){
        _lastSampleTime = systemTime();
        _lastSample = sample;
        _initialized = true;
        return;
      }      
      
      Time t_sys = systemTime();
      Time dt = t_sys - _lastSampleTime;
      Real delta = sample-_lastSample;
      Real currentRate = delta /dt ;

      _average.addSample(currentRate);

      _lastSample = sample;
      _lastSampleTime =t_sys;

    }

    Real calculate(){
      return _average.calculate();
    }

  };
  }