#pragma once

#include <core.reflection/action/Action.h>

namespace nspace{
  template<typename T=std::function<void()> >
  class DelegateAction : public virtual Action{
    TYPED_OBJECT(DelegateAction)
  private:
    T _callback;
  public:
    DelegateAction(T callback):_callback(callback){}
  protected:
    void executeAction(){
      _callback();
    };
  };
}