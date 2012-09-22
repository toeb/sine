#pragma once
#include <config.h>
#include <queue>
#include <math.statistics/IAverage.h>
namespace nspace{

class Average : IAverage{
  std::queue<Real> _queue;
  int _samples;
public:
  Average(int samples = 50):_samples(samples){}

  void addSample(Real sample){
    _queue.push(sample);
  }

  Real calculate(){
    Real result = 0;
    for(int i =0; i < _samples;i++){
      Real val = _queue.front();
      _queue.pop();
      result+=val;
      _queue.push(val);
    }
    return result / _samples;
  }
};
}