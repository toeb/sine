#ifndef __ISimulationObject_h__
#define __ISimulationObject_h__
namespace IBDS{
class ISimulationObject{
protected:
  virtual int getId(){return 0;}
};
}
#endif