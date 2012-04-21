#pragma once
#include "Simulation/ISimulationObject.h"
namespace IBDS {
	class Body : public ISimulationObject, public IIntegrable
	{
	public:
	    virtual void resetForce() = 0;
		virtual Real getMass()const = 0;
		virtual void addExternalForce(const IBDS::Vector3D & f) = 0;
	};
	}