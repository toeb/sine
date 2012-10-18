#pragma once
#include <core/Object.h>
namespace nspace{
  /**
  * represents a task.  The Run Method needs to be implemented
  */
class ITask: public virtual Object{
  TYPED_OBJECT(ITask);
public:
  // run may do anything.  if the task ongoing you need to make sure, that the implementation of run is fast
  // especially if the task is to be real time
	virtual void run()=0;
};

}
