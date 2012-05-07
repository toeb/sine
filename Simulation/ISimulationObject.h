#ifndef __ISimulationObject_h__
#define __ISimulationObject_h__

#include <Math/Vector3D.h>

namespace IBDS{
class ISimulationObject {
protected:
public:
  virtual void render() const = 0;
};
}
#endif