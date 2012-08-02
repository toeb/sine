#include "CompositeStatefulObject.h"

using namespace nspace;
using namespace std;






void CompositeStatefulObject::exportDerivedState(IState & xDot)const{
  unsigned int currentOffset = 0;
  foreachComponent([&currentOffset, &xDot](IStatefulObject * integrable){
		unsigned int dim = integrable->stateDimension();
		StateRange range(xDot,currentOffset,dim);
		integrable->exportDerivedState(range);
    currentOffset +=dim ;
  });
}


void CompositeStatefulObject::exportState(IState &  x) const{
  unsigned int currentOffset = 0;
  foreachComponent([&currentOffset, &x](IStatefulObject * integrable){
		unsigned int dim = integrable->stateDimension();
		StateRange range(x,currentOffset,dim);
		integrable->exportState(range);
    currentOffset +=dim ;
  });
}

void CompositeStatefulObject::importState(const IState &  x){
   unsigned int currentOffset = 0;
  foreachComponent([&currentOffset, &x](IStatefulObject * integrable){
		unsigned int dim = integrable->stateDimension();
		const StateRange range(x,currentOffset,dim);
		integrable->importState(range);
    currentOffset +=dim ;
  });

  
}
unsigned int CompositeStatefulObject::stateDimension()const{
  unsigned int result =0U;
  foreachComponent( [&result](IStatefulObject * integrable){
    result += integrable->stateDimension();
  });
  return result;
}

unsigned int CompositeStatefulObject::availableDerivatives()const{
  unsigned int result = 0U;
  foreachComponent( [&result](IStatefulObject * integrable){
    unsigned int currentDerivatives =integrable->availableDerivatives();
    if(result < currentDerivatives){
      result = currentDerivatives;
    }
  });
  return result;
}
