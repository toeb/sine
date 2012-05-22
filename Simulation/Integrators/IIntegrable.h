#ifndef __Integratable_h__
#define __Integratable_h__
#include <Math/VectorND.h>
#include <Simulation/ISimulationObject.h>
//#include <Simulation/ISimulationObject.h>
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
class IIntegrable : public virtual ISimulationObject{
public:

  virtual bool hasStateDimensionChanged(){return false;}
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
   * \brief Gets the last derived state.
   *
   * \author Tobias Becker
   * \date 16.04.2012
   *
   * \param [in,out] xDot If non-null, the x coordinate dot.
   */
  virtual void getDerivedState(Real * xDot)const=0;

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