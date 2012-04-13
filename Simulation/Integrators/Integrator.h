#ifndef __Integrator_h__
#define __Integrator_h__
#include "IIntegrable.h"
namespace IBDS{

/**
 * <summary> Abstract Integrator class.</summary>
 *
 * <remarks> Tobias Becker, 13.04.2012.</remarks>
 */
class Integrator{
private:
  /// <summary> The integratable </summary>
  IIntegrable * _integratable;
  int _dimension;
  VectorND * _x;
  VectorND * _xNext;
  VectorND * _xDot;
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
   * <summary> Integrates the integratable object over the intervall [a,b]. the initial value is
   *           managed by the integratable.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="a"> beginning of the interval </param>
   * <param name="b"> end of the interval </param>
   */
  void integrate(const Real & a, const Real & b);

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
  const VectorND& f(const VectorND & x);
  virtual void doIntegration(const VectorND& x_0, VectorND& x_i, const Real& a, const Real& b)=0;
};
}
#endif