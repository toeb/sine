#include "Observable.h"
#include <core/Query.h>
using namespace nspace;


Observable::Observable():_observers(0){}
Observable::~Observable(){if(hasObservers())delete _observers; _observers=0;}
bool Observable::hasObservers()const{
  return _observers!=0;
}
Observable::ObserverList & Observable::observers(){
  if(!_observers)_observers= new ObserverList();
  return * _observers;
}
void Observable::raiseObjectChanged(){
  onChange();
  if(!hasObservers())return;
  std::for_each(observers().begin(),observers().end(),[this](ObjectObserver * observer){
    observer->onChange(this);
  });
}
void Observable::addObjectObserver(ObjectObserver* oo){
  observers().push_back(oo);
}
void Observable::removeObjectObserver(ObjectObserver * oo){
  if(!hasObservers())return;
  Query<ObjectObserver*>::remove(observers(),oo);
}