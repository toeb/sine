#pragma once
#include <Simulation/SimulationModuleBase.h>
#include <Simulation/Textiles/TextileModel.h>
namespace IBDS{
class TextileAlgorithm: public virtual SimulationModuleBase<TextileModel>{
public:
  void normalize();
};
}