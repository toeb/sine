#ifndef __ExplicitEuler_h__
#define __ExplicitEuler_h__
#include "../SingleStepIntegrator.h"
namespace IBDS{
class ExplicitEuler : public SingleStepIntegrator{
private:
public:
  ExplicitEuler(Real stepLength=0.01);
protected:
  void doStep(const Real & h, VectorND & x_i);
};
}
#endif