#include "CompositeIntegratable.h"
#include <algorithm>
using namespace IBDS;
using namespace std;


CompositeIntegratable::CompositeIntegratable(){
}

bool  CompositeIntegratable::addSimulationObject(ISimulationObject  * object){
  auto integrable = dynamic_cast<IIntegrable*>(object);
  if(!integrable)return false;

  _children.push_back(integrable);
  return true;
}
bool CompositeIntegratable::removeSimulationObject(ISimulationObject * object){
  auto integrable = dynamic_cast<IIntegrable*>(object);
  if(!integrable)return false;

  auto pos = find(_children.begin(), _children.end(), object);
  if(pos == _children.end())return false;

  _children.erase(pos);
  return true;
}
void CompositeIntegratable::getDerivedState(Real * xDot)const{
  int currentOffset = 0;
  for(vector<IIntegrable*>::const_iterator it = _children.begin(); it != _children.end(); it++){
    IIntegrable & integratable = **it;
    integratable.getDerivedState(xDot+currentOffset);
    currentOffset += integratable.getStateDimension();
  }
}


void CompositeIntegratable::getState(Real * x) const{
  int currentOffset = 0;
  for(vector<IIntegrable*>::const_iterator it = _children.begin(); it != _children.end(); it++){
    IIntegrable & integratable = **it;
    integratable.getState(x+currentOffset);
    currentOffset += integratable.getStateDimension();
  }
}

void CompositeIntegratable::setState(const Real * x){
   int currentOffset = 0;
  for(vector<IIntegrable*>::const_iterator it = _children.begin(); it != _children.end(); it++){
    IIntegrable & integratable = **it;
    integratable.setState(x+currentOffset);
    currentOffset += integratable.getStateDimension();
  }
}
int CompositeIntegratable::getStateDimension()const{
  int result =0;
  for(vector<IIntegrable*>::const_iterator it = _children.begin(); it != _children.end(); it++){
    result += (*it)->getStateDimension();
  }
  return result;
}