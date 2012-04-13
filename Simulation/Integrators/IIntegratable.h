#ifndef __Integratable_h__
#define __Integratable_h__
#include <Math/VectorND.h>

namespace IBDS{
class IIntegratable{
public:

  /**
   * <summary> Evaluates this integratable at state x.  returns stores the derived state
   * 					 in xDot.
   * 					 the state is autonomous - if time is needed subclasses
   * 					 can store 1 in xDot to get the current time.
   * 					 this might cause redundancies because multiple bodies 
   * 					 might need time. but for now this is not important</summary>
   *
   * <remarks> Tobi, 12.04.2012.</remarks>
   *
   * <param name="state">        The time.</param>
   * <param name="derivedState"> [in,out] The state.</param>
   *
   */
  virtual void evaluate(const Real * x, Real * xDot) = 0;

  /// <summary> Sets the state this integratable.</summary>
  ///
  /// <remarks> Tobi, 12.04.2012.</remarks>
  ///
  /// <param name="x"> The state.</param>
  void virtual setState(const Real * state)=0;

  /// <summary> Gets the state of this integratable.</summary>
  ///
  /// <remarks> Tobi, 12.04.2012.</remarks>
  ///
  /// <returns> The state.</returns>
  virtual void getState(Real * state)const=0;

  /**
   * <summary> Gets the dimension of the state of this iintegratable
   * 					 .</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <returns> The state dimension.</returns>
   */
   virtual int getStateDimension()const=0;
};

}
#endif