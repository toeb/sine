#ifndef __CustomSimulation_h__
#define __CustomSimulation_h__

#include <Simulation/RenderingSimulation.h>


namespace IBDS{
class CustomSimulation : public RenderingSimulation{
protected:
  void buildModel();
public:
};
}
#endif