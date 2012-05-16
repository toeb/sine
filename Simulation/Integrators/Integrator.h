#ifndef __Integrator_h__
#define __Integrator_h__
#include "IIntegrable.h"
#include <Simulation/ISimulationModule.h>
#include <Simulation/Integrators/ISystemFunction.h>
namespace IBDS{
  
/**
 * <summary> Abstract Integrator class.</summary>
 *
 * <remarks> Tobias Becker, 13.04.2012.</remarks>
 */
class Integrator : public ISimulationObject{
private:
  /// <summary> The integratable </summary>
  IIntegrable * _integratable;
  ISystemFunction * _systemFunction;
  int _dimension;
  VectorND _x;
  VectorND _xNext;
  VectorND _xDot;
public:

  /**
   * <summary> Default constructor.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   */
  Integrator();

  /**
   * <summary> Destructor.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   */
  ~Integrator();

  /**
   * \brief Integrates the integratable object over the intervall [a,b]. the initial value is managed
   *        by the integratable.
   *
   * \param a beginning of the interval.
   * \param b end of the interval.
   *
   * \return  the actual end of the interval .
   *
   * ### remarks  Tobias Becker, 13.04.2012.
   */
  Real integrate(Real a, Real b);
  
  /**
   * <summary> Gets the integratable.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <returns>  the integratable.</returns>
   */
  IIntegrable * getIntegratable();

  /**
   * <summary> Sets the integratable.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="integratable"> [in] the integratable.</param>
   */
  void setIntegratable(IIntegrable * integratable);

  void setSystemFunction(ISystemFunction & systemFunction);
  ISystemFunction * getSystemFunction();
  /**
   * <summary> Gets the state.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <returns> The state.</returns>
   */
  const VectorND & getState()const;
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
  const VectorND& f(Real t, const VectorND & x, Real h);

  /**
   * \brief Executes the integration operation. 
   *
   * \param x_0           The initial state.
   * \param [in,out]  x_i The integrated state .
   * \param a             beginning of the integration interval.
   * \param b             The the end of the integration interval.
   *
   * \return  the actual end of the integration interval.  (The integration methods might need to integrate further than the wantedboundary b).
   */
  virtual Real doIntegration(const VectorND& x_0, VectorND& x_i, Real a, Real b)=0;
};
}


#endif