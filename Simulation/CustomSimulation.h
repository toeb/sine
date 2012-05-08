#ifndef __CustomSimulation_h__
#define __CustomSimulation_h__

#include <Simulation/RenderingSimulation.h>


namespace IBDS{
class CustomSimulation : public RenderingSimulation{
private:
//  IntegratorsManager* _integratorManager;
protected:
  void buildModel();
  void applyExternalForces();
};
}
#endif