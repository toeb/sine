#include "RealTimeProvider.h"

using namespace nspace;
const RealTimeProvider & RealTimeProvider::defaultInstance(){
  static RealTimeProvider * _defaultInstance = 0;
  if(!_defaultInstance)_defaultInstance=new RealTimeProvider();
  return * _defaultInstance;
}
RealTimeProvider::RealTimeProvider():_t0(applicationTime()){setName("RealTimeProvider");}
inline Time RealTimeProvider::time() const{
  return applicationTime()-_t0;
};