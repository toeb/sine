#pragma once

#include <functional>
#include <Visualization\UserInterface\IAction.h>

namespace IBDS{

class DelegateAction : public virtual IAction{
private:
  std::function<void()>  _function;
public:
  DelegateAction(const std::string & name, std::function<void()>  function);
  void execute();
};
}