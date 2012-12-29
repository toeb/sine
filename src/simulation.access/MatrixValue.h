#pragma once
#include <simulation.access/IValue.h>
namespace nspace{
  class MatrixValue : public IValue{
    REFLECTABLE_OBJECT(MatrixValue);
  public:
    virtual int rows()const=0;
    virtual int cols()const=0;
    virtual Real & value(int i, int j)=0;
    virtual const Real value(int i, int j)const=0;
  };
}
