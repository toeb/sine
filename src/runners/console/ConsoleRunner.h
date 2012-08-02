#pragma once
#include <simulation/runner/SimulationRunner.h>

namespace nspace{
  class ConsoleRunner : public SimulationRunner{
    virtual int executeRunner(){return false;}
    virtual bool initializeRunner(){return false;}
  };
}