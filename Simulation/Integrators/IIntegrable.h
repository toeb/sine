#ifndef __Integratable_h__
#define __Integratable_h__
#include <Math/VectorND.h>

namespace IBDS{

/**
 * <summary> Super class of integrable objects.
 * 					 Allows access to the state and evaluation of the object
 * 					 The state is an Real array.  
 * 					 The subclasses need to be aware of the implications
 * 					 of writing or reading data out of range .</summary>
 *
 * <remarks> Tobias Becker, 13.04.2012.</remarks>
 */
class IIntegrable{
public:

  /**
   * <summary> Evaluates this integratable at state x.  returns stores the derived state in xDot.
   *           the state is autonomous - if time is needed subclasses can store 1 in xDot to get the
   *           current time. this might cause redundancies because multiple bodies might need time.
   *           but for now this is not important.</summary>
   *
   * <remarks> Tobi, 12.04.2012.</remarks>
   *
   * <param name="x">    The state.</param>
   * <param name="xDot"> [out] The derived state.</param>
   */
  virtual void evaluate(const Real * x, Real * xDot) = 0;

  /**
   * <summary> Sets the state this integratable.</summary>
   *
   * <remarks> Tobi, 12.04.2012.</remarks>
   *
   * <param name="state"> The state.</param>
   */
  void virtual setState(const Real * state)=0;

  /**
   * <summary> Gets the state of this integratable.</summary>
   *
   * <remarks> Tobi, 12.04.2012.</remarks>
   *
   * <param name="state"> [out] the state.</param>
   *
   */
  virtual void getState(Real * state)const=0;

  /**
   * <summary> Gets the dimension of the state of this IIntegrable
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