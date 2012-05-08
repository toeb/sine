#pragma once
#include "Simulation/ISimulationObject.h"
#include <Simulation/Integrators/IIntegrable.h>
#include <Math/Vector3D.h>
namespace IBDS {
	class Body : public IIntegrable
	{
	public:
	  virtual void resetForce() = 0;
		virtual Real getMass()const = 0;
		virtual void addExternalForce(const IBDS::Vector3D & f) = 0;
	};
	}