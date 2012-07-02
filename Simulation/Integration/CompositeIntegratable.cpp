#include "CompositeIntegratable.h"
#include <algorithm>
using namespace IBDS;
using namespace std;


CompositeIntegratable::CompositeIntegratable():_currentState(0){
}
bool CompositeIntegratable::hasStateDimensionChanged(){
  return _dimensionChanged;
}
bool  CompositeIntegratable::addSimulationObject(ISimulationObject  * object){
  auto integrable = dynamic_cast<IIntegrable*>(object);
  if(!integrable)return false;

  _children.push_back(integrable);
  _dimensionChanged=true;
  return true;
}
bool CompositeIntegratable::removeSimulationObject(ISimulationObject * object){
  auto integrable = dynamic_cast<IIntegrable*>(object);
  if(!integrable)return false;

  auto pos = find(_children.begin(), _children.end(), object);
  if(pos == _children.end())return false;

  _children.erase(pos);
   _dimensionChanged=true;
  return true;
}
void CompositeIntegratable::getDerivedState(Real * xDot)const{
  int currentOffset = 0;
   for_each( _children.begin(), _children.end(), [&currentOffset, &xDot](IIntegrable * integrable){
    integrable->getDerivedState(xDot+currentOffset);
    currentOffset += integrable->getStateDimension();
  });
}


void CompositeIntegratable::getState(Real * x) const{
  
  int currentOffset = 0;
   for_each( _children.begin(), _children.end(), [&currentOffset, &x](IIntegrable * integrable){
     integrable->getState(x+currentOffset);
     currentOffset += integrable->getStateDimension();
   });
}

void CompositeIntegratable::setState(const Real * x){

   int currentOffset = 0;
   for_each( _children.begin(), _children.end(), [&currentOffset, &x](IIntegrable * integrable){
    integrable->setState(x+currentOffset);
    currentOffset += integrable->getStateDimension();
   });

  
}
int CompositeIntegratable::getStateDimension()const{
  int result =0;
  for(vector<IIntegrable*>::const_iterator it = _children.begin(); it != _children.end(); it++){
    result += (*it)->getStateDimension();
  }
  return result;
}
//
//void CompositeIntegratable::setDerivedStateDataArray(Real * dState){
//  int currentOffset = 0;
//  for_each(_children.begin(), _children.end(), [&currentOffset, &dState](IIntegrable* integrable){
//    integrable->setDerivedStateDataArray(dState+currentOffset);
//    currentOffset += integrable->getStateDimension();
//  });
//}
//void CompositeIntegratable::setStateDataArray(Real * state){
//  int currentOffset = 0;
//
//  for_each(_children.begin(), _children.end(), [&currentOffset, &state](IIntegrable* integrable){
//    integrable->setStateDataArray(state+currentOffset);
//    currentOffset += integrable->getStateDimension();
//  });
//}