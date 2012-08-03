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
  int _valueCount;
  Real _valueSum;
  int _maxPoolCount;
  int _poolCount;
  std::queue<AverageOverTimeValue*> _values;
  std::queue<AverageOverTimeValue*> _freeStructs;
  Time timeLength;

public:
  AverageOverTime(Time tl):timeLength(tl),_maxPoolCount(4000),_valueCount(0),_valueSum(0),_poolCount(0){}
  AverageOverTimeValue * createValue(){
    AverageOverTimeValue * av;
    if(_freeStructs.empty()){
      av = new AverageOverTimeValue();
    }else{
      av = _freeStructs.front();
      _freeStructs.pop();
      _poolCount--;
    }
    return av;
  }
  void freeValue(AverageOverTimeValue * value){
    if(_freeStructs.size() > _maxPoolCount){
      delete value;
      return;
    }
    _poolCount++;
    _freeStructs.push(value);    
  }
  void addSample(Real value){    
    AverageOverTimeValue * av = createValue();
    
    av->t = applicationTime();
    av->value = value;

    _valueSum += value;
    _valueCount++;
    _values.push(av);
  }

  void removeOldSamples(){
    AverageOverTimeValue * current;
    Time t = applicationTime()-timeLength;
    while(_valueCount){
      current = _values.front();
      if(current->t > t)break;
      _values.pop();
      
      _valueSum-=current->value;
      _valueCount--;
      freeValue(current);
        
    }
    
  }
  Real calculate(){
    removeOldSamples();
    if(!_valueCount)return 0.0;
    return _valueSum / _valueCount;
  }

};
}