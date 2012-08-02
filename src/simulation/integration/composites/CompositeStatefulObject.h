#pragma once
#include <common/patterns/Composite.h>
#include <simulation/integration/IStatefulObject.h>
namespace nspace{

/**
 * <summary> Composite stateful object. A class which contains multiple IIntegrables as
 * 					 Children.  (Composite Pattern)</summary>
 *
 * <remarks> Tobias Becker, 13.04.2012.</remarks>
 */
class CompositeStatefulObject : public Composite<IStatefulObject>, public virtual IStatefulObject{
public:  
  unsigned int stateDimension()const;
  unsigned int availableDerivatives()const;
protected:
  void exportDerivedState(IState & xDot)const;
  void importState(const IState & state);
  void exportState(IState & state)const;

};
}