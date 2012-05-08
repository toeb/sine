#ifndef __Force_h__
#define __Force_h__

#include "Body.h"
#include "Common/Config.h"
#include <Vector>
#include <Visualization/IRenderer.h>
#include <Visualization/MiniGL.h>

namespace IBDS {
	class Force: public ISimulationObject
	{
	public:
		/**
		 * Apply this force.
		 * \param target reference to the simulation objects that can be applied a force to.
		 * \param time simulation time
		 */
		virtual void act(std::vector<Body*> & target, Real time) = 0;
   
  };
	}
#endif