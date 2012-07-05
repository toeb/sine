#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <vector>
#include <functional>
namespace IBDS{
typedef std::function<void(ISimulationObject*)> SimulationObjectAction;
class CompositeSimulationObject : public virtual ISimulationObject{
private:
  std::vector<ISimulationObject*> _children;
public:
  CompositeSimulationObject();
  ~CompositeSimulationObject();

  void addChild(ISimulationObject* object);
  bool removeChild(ISimulationObject * object);

  const std::vector<ISimulationObject*> & children()const;
  void forEachChild(SimulationObjectAction action) ;
  void forAllChildren(SimulationObjectAction action);
protected:
  bool initializeObject();
  void cleanupObject();
};
}