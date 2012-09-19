#pragma once
#include <simulation/core/wrapper/Wrapper.h>
#include <functional>

namespace mbslib{	
class DelegateWrapper:public Wrapper{
private:
  std::function<ISimulationObject* (ISimulationObject*)> _wrapDelegate;
public:
  DelegateWrapper(std::function<ISimulationObject * (ISimulationObject * ) > wrapFunc):_wrapDelegate(wrapFunc){

  }
  ISimulationObject * wrap(ISimulationObject * object){
    return _wrapDelegate(object);
  }
};
}