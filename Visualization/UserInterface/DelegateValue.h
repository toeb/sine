#pragma once

#include <Simulation/Core/ISimulationObject.h>
#include <Visualization/UserInterface/IValue.h>
#include <Visualization\UserInterface\IComponent.h>
#include <functional>
namespace IBDS{

/**
 * \class DelegateValue
 * 				allows easy getter setter functionality for any value specific by type argument T.  
 * 				expects a std::function as  a getter and a setter
 *
 * \brief Delegate value.
 */
template<class T>
class DelegateValue : public virtual IValue{
private:
  std::function<void (T)> _setter;
  std::function<T ()> _getter;
public:
  DelegateValue(const std::string & name, std::function<T()> getter, std::function<void (T)> setter);
  void set(const void * value);
  void get(void * value);
};
}