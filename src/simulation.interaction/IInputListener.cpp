#include "IInputListener.h"
#include <simulation.interaction/InputHandler.h>
using namespace nspace;

InputHandler * IInputListener::currentHandler()const{
  if(_currentHandler)return _currentHandler;
  Set<InputHandler*> tmp = _handlers;
  tmp.sort([](const InputHandler * a, const InputHandler * b){
    return a->lastChange() > b->lastChange();
  });
  return tmp.first();
}
IInputListener::IInputListener():_currentHandler(0){
}

void IInputListener::setCurrentHandler(InputHandler * handler){
  _currentHandler = handler;
}