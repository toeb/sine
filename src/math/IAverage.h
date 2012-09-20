#pragma once
#include <queue>
#include <config.h>
namespace nspace{
class IAverage{
public:
  virtual void addSample(Real value)=0;
  virtual Real calculate()=0;
};

}