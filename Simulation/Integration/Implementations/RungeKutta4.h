#pragma once
#include <Simulation/Integration/SingleStepIntegrator.h>
namespace IBDS{
class RungeKutta4 : public SingleStepIntegrator{
public:
  RungeKutta4(Real h = 0.05);
protected:
  void doStep(Real t_i,VectorND & x_i, Real h);
};
}