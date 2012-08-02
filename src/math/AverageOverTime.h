#pragma once
#include <common/Time.h>
#include <math/IAverage.h>
#include <queue>

namespace nspace{
struct AverageOverTimeValue{
  Time t;
  Real value;
};
class AverageOverTime : public IAverage{
private:
  std::queue<AverageOverTimeValue*> _values;
  Time timeLength;

public:
  AverageOverTime(Time tl):timeLength(tl){}

  void addSample(Real value){
    AverageOverTimeValue * av = new AverageOverTimeValue();

    av->t = applicationTime();
    av->value = value;
    _values.push(av);
  }

  Real calculate(){
    Real value=0.0;
    if(!_values.size())return 0.0;
    int count=0;
    AverageOverTimeValue * first = _values.front();
    if(!first)return value;
    AverageOverTimeValue * current;
    Time t = applicationTime()-timeLength;
    while(true){
      current = _values.front();
      if(!current)break;
      _values.pop();

      if(current->t < t){
        if(!_values.size())break;
        first = _values.front();
        delete current;
        continue;
      }
      
      value += current->value;
      count ++;
      _values.push(current);
      if(_values.front()==first)break;
    }
    value = value / count;
    return value;    
  }

};
}