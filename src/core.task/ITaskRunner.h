#pragma once

#include <core.task/ITask.h>
namespace nspace{

  class ITaskRunner{
  public:
    virtual void runTask(ITask task)=0;
  };

}