#ifndef __CompositeIntegratable_h__
#define __CompositeIntegratable_h__
#include <vector>
#include "IIntegratable.h"
namespace IBDS{
class CompositeIntegratable : public IIntegratable{
private:
  std::vector<IIntegratable*> _children;
public:
  CompositeIntegratable();
  void addIntegratable(IIntegratable * iintegratable);
 
  virtual void evaluate(const Real * x, Real * xDot);
  void virtual setState(const Real * state);
   virtual void getState(Real * state)const;
   virtual int getStateDimension()const;
};
}
#endif