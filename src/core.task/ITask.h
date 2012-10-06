#pragma once

#include <core/Object.h>
namespace nspace{
class ITask: public virtual Object{
  TYPED_OBJECT(ITask);
public:
	virtual void run()=0;
};
}
