#pragma once

#include <simulation/dynamics/DynamicBody.h>
#include <vector>

namespace nspace {
	class Force: public virtual ISimulationObject
	{
	public:
		/**
		 * Apply this force.
		 * \param target reference to the simulation objects that can be applied a force to.
		 * \param time simulation time
		 */
		virtual void act(std::vector<DynamicBody*> & target, Real time) = 0;
   
  };
	}
