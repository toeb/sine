#include "CompositeIntegratable.h"

using namespace IBDS;
using namespace std;


CompositeIntegratable::CompositeIntegratable(){
  _children = new vector<IIntegrable*>();
}

void CompositeIntegratable::addIntegratable(IIntegrable  * integratable){
  _children->push_back(integratable);
}

void CompositeIntegratable::evaluate(const Real * x, Real * xDot){
  int currentOffset = 0;
  for(vector<IIntegrable*>::const_iterator it = _children->begin(); it != _children->end(); it++){
    IIntegrable & integratable = **it;
    integratable.evaluate(x+currentOffset, xDot+currentOffset);
    currentOffset += integratable.getStateDimension();
  }
}

void CompositeIntegratable::getState(Real * x) const{
  int currentOffset = 0;
  for(vector<IIntegrable*>::const_iterator it = _children->begin(); it != _children->end(); it++){
    IIntegrable & integratable = **it;
    integratable.getState(x+currentOffset);
    currentOffset += integratable.getStateDimension();
  }
}

void CompositeIntegratable::setState(const Real * x){
   int currentOffset = 0;
  for(vector<IIntegrable*>::const_iterator it = _children->begin(); it != _children->end(); it++){
    IIntegrable & integratable = **it;
    integratable.setState(x+currentOffset);
    currentOffset += integratable.getStateDimension();
  }
}
int CompositeIntegratable::getStateDimension()const{
  int result =0;
  for(vector<IIntegrable*>::const_iterator it = _children->begin(); it != _children->end(); it++){
    result += (*it)->getStateDimension();
  }
  return result;
}