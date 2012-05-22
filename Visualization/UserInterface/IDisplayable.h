#pragma once
#include <Simulation\ISimulationObject.h>
namespace IBDS{

class IUserInterface;
class IDisplayable  : public virtual ISimulationObject{
private:
  bool _visible;
public:
  IDisplayable();
  ~IDisplayable();
  void setVisible();
  bool isVisible()const;
protected:
  virtual void setupUi(IUserInterface * ui);
  
};
}
