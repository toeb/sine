#pragma once
#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Textiles/TextileModel.h>
namespace IBDS{
class TextileAlgorithm: public virtual SimulationModuleBase<TextileModel>{
public:
  Real getSuggestedStepSize();
  void normalize();
};
}