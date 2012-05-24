#pragma once

#include <Simulation/Integrators/SingleStepIntegrator.h>

namespace IBDS{
class ImplicitEuler : public SingleStepIntegrator{
private:
  VectorND _tmp,_x_next;
  Real _tolerance;
  int _maxIterations;
public:
  ImplicitEuler(Real stepLength=0.01, int maxIterations=100, Real tolerance = 10e-5);
protected:
  void doStep(Real t_i, VectorND & x_i, Real h);
};
}
