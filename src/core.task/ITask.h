#pragma once
#include <core/Object.h>
#include <core/NamedObject.h>
#include <core/PropertyChangingObject.h>
#include <core.h>
namespace nspace{
  /**
  * represents a task.  The Run Method needs to be implemented
  */
  class ITaskRunner;

  class ITask: public virtual NamedObject, public virtual PropertyChangingObject{
    reflect_type(nspace::ITask);
    typedef ITaskRunner* extensible_property(TaskRunner);
    typedef uint reflect_property(NumberOfTimes);
  public:
    ITask():_TaskRunner(0),_NumberOfTimes(0){}
    // run may do anything.  if the task ongoing you need to make sure, that the implementation of run is fast
    // especially if the task is to be real time
    virtual void run()=0;
  };
}
