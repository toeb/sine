
#include "IInputListener.h"
#include <simulation.interaction/InputHandler.h>
using namespace nspace;


InputHandler * IInputListener::currentHandler()const{
  Set<InputHandler*> tmp = _handlers;
  tmp.sort([](const InputHandler * a, const InputHandler * b){
    return a->lastChange() > b->lastChange();
  });
  return tmp.first();

}