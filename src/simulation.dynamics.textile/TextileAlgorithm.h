#pragma once
#include <simulation/SimulationModuleBase.h>
#include <simulation.timing/Timeable.h>
#include <simulation.dynamics.textile/TextileModel.h>
namespace nspace{
  class TextileModule: public SimulationModuleBase<TextileModel>, public virtual Timeable{
  public:
    TextileModule(){
      setName("Textile Module");
    }
    Real getSuggestedStepSize();
    void normalize();
  };
}