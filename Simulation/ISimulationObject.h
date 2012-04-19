#ifndef __ISimulationObject_h__
#define __ISimulationObject_h__

#include "Simulation/Integrators/IIntegrable.h"
#include <Math/Vector3D.h>

namespace IBDS{
class ISimulationObject : public IIntegrable {
protected:
  virtual int getId(){return 0;}

public:
	virtual void render() const = 0;
};
}
#endif