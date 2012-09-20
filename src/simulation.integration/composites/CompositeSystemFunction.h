#pragma once

#include <simulation.integration/ISystemFunction.h>
#include <core/patterns/Composite.h>

namespace nspace{


class CompositeSystemFunction : public Composite<ISystemFunction>, public virtual ISystemFunction{
public:  
	void preIntegration(Time t, Time h);
	void evaluate(Time t, Time h);
  void postIntegration(Time t, Time h);
};

}
