#pragma once

#include <simulation.time/ITimeProvider.h>

namespace nspace{

class RealTimeProvider:public virtual ITimeProvider{
private:
  Time _t0;
  static RealTimeProvider * _defaultInstance;
public:
  static inline const RealTimeProvider & defaultInstance(){
    return * _defaultInstance;
  }
  RealTimeProvider():_t0(applicationTime()){setName("RealTimeProvider");}
  inline Time time() const{
    return applicationTime()-_t0;
  };
};

}