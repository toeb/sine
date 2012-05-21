#ifndef __CompositeIntegratable_h__
#define __CompositeIntegratable_h__
#include <vector>
#include "IIntegrable.h"
#include <Simulation/ISimulationModule.h>
namespace IBDS{

/**
 * <summary> Composite integratable. A class which contains multiple IIntegrables as
 * 					 Children.  (Composite Pattern)</summary>
 *
 * <remarks> Tobias Becker, 13.04.2012.</remarks>
 */
class CompositeIntegratable : public virtual IIntegrable, public virtual ISimulationModule{
private:
  /// <summary> The children of this composite</summary>
  std::vector<IIntegrable*> _children;
  bool _dimensionChanged;
public:
  bool hasStateDimensionChanged();
  CompositeIntegratable();
  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);

  virtual void getDerivedState(Real * xDot)const;
  void virtual setState(const Real * state);
  virtual void getState(Real * state)const;
  virtual int getStateDimension()const;
};
}
#endif