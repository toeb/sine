#ifndef __SingleStepIntegrator_h__
#define __SingleStepIntegrator_h__
#include "Integrator.h"
#include <Math/VectorND.h>
namespace IBDS{
class SingleStepIntegrator : public Integrator{
private:
  
  /// <summary> The timestep length h </summary>
  Real _h;

public:
  /**
   * <summary> Integrates.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="initialValue"> The initial value.</param>
   * <param name="a">            a.</param>
   * <param name="b">            The b.</param>
   *
   * <returns> .</returns>
   */
  void doIntegration(const VectorND& x_0, VectorND& x_i, const Real & a, const Real& b);

  /**
   * <summary> Sets a step size.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="h"> The h.</param>
   */
  void setStepSize(Real h);

  /**
   * <summary> Gets the step size.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <returns> The step size.</returns>
   */
  Real getStepSize();

protected:
  /**
   * <summary> Executes an integration step.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   */
  virtual void  doStep(const Real & h, VectorND & x_i)=0;

};
}
#endif