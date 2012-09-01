#pragma once
#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Core/Timing/Timeable.h>
#include <Simulation/Textiles/TextileModel.h>
namespace IBDS{
class TextileModule: public SimulationModuleBase<TextileModel>, public virtual Timeable{
public:
  TextileModule(){
    setName("Textile Module");
  }
  Real getSuggestedStepSize();
  void normalize();
};
}