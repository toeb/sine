#ifndef __Force_h__
#define __Force_h__

#include "ISimulationObject.h"
#include "Common/Config.h"

namespace IBDS {
class Force
	{
	public:
		Force(void);
		~Force(void);
		virtual void apply(std::vector<ISimulationObject*> & target, Real time) const = 0;
	};
	}
#endif