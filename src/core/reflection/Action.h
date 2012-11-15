#pragma once

#include <core/Object.h>

namespace nspace{
  
class Action{
  TYPED_OBJECT(Action);
public:
  void execute(){executeAction();}
protected:
  virtual void executeAction()=0;
};
}