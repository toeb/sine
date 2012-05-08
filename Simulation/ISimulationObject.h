#pragma once
namespace IBDS{
class ISimulationObject {
public:
  virtual bool initialize(){return true;};
  virtual void cleanup(){};
};
};
