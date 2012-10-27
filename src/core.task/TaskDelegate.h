#pragma once

#include <core.task/ITask.h>

namespace nspace{
  template<typename T=std::function<void()> >
  class TaskDelegate : public virtual ITask{
    T & _callback;
  public:
    TaskDelegate(T & callback):_callback(callback){}
    void run(){_callback();}
  };

  template<>
  class TaskDelegate<std::function<void()> >{
    std::function<void()> _callback;
  public:
    TaskDelegate(std::function<void()> callback):_callback(callback){}
    void run(){_callback();}

  };
}