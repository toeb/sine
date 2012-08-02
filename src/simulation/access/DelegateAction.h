#pragma once

#include <functional>

#include <simulation/access/IAction.h>

namespace nspace{

class DelegateAction : public virtual IAction{
private:
  std::function<void()>  _function;
public:
  DelegateAction(const std::string & name, std::function<void()>  function);
  void execute();
};
}