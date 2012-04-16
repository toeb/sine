#ifndef __CompositeIntegratable_h__
#define __CompositeIntegratable_h__
#include <vector>
#include "IIntegrable.h"
namespace IBDS{

/**
 * <summary> Composite integratable. A class which contains multiple IIntegrables as
 * 					 Children.  (Composite Pattern)</summary>
 *
 * <remarks> Tobias Becker, 13.04.2012.</remarks>
 */
class CompositeIntegratable : public IIntegrable{
private:
  /// <summary> The children of this composite</summary>
  std::vector<IIntegrable*> * _children;
public:

  /**
   * <summary> Default constructor.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   */
  CompositeIntegratable();

  /**
   * <summary> Adds an integratable to this composite.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="IIntegrable"> [in,out] If non-null, the IIntegrable.</param>
   */
  void addIntegratable(IIntegrable * IIntegrable);

  /**
   * <summary> Evaluates this composite Integratable object by 
   * 					 evaluating each of its children</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="x">    The state.</param>
   * <param name="xDot"> [out] the derived state.</param>
   */
  virtual void evaluate();

  virtual void getDerivedState(Real * xDot)const;

  /**
   * <summary> Sets the state of all children</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   *
   * <param name="state"> The state.</param>
   */
  void virtual setState(const Real * state);

   /**
    * <summary> Gets the state of all chidlren.</summary>
    *
    * <remarks> Tobias Becker, 13.04.2012.</remarks>
    *
    * <param name="state"> [out] the state.</param>
    */
   virtual void getState(Real * state)const;

   /**
    * <summary> Gets the state's dimension.</summary>
    *
    * <remarks> Tobias Becker, 13.04.2012.</remarks>
    *
    * <returns> The state's dimension.</returns>
    */
   virtual int getStateDimension()const;
};
}
#endif