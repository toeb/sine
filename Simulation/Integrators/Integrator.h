#ifndef __Integrator_h__
#define __Integrator_h__
#include "IIntegratable.h"
namespace IBDS{
class Integrator{
private:
  IIntegratable * _integratable;
  Real * _x;
  Real * _xDot;
public:
  void Integrate(Real from, Real to);
  IIntegratable * getIntegratable();
  void setIntegratable(IIntegratable * integratable);
protected:
  /**
   * <summary> evaluates the function at state x</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="x"> The x coordinate.</param>
   *
   * <returns> null if it fails, else.</returns>
   */
  const Real * f(const Real * x);
  virtual void doIntegration(Real from, Real to)=0;
};
}
#endif