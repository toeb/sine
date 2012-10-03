#include "InputHandler.h"

#include <simulation.interaction/IInputListener.h>
using namespace nspace;

Set<IInputListener* > & InputHandler::listeners(){return _listeners;}
const Set<IInputListener* > & InputHandler::listeners()const{return _listeners;}


void InputHandler::onAcception(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(!listener)return;
  listener->_handlers |= this;
  _listeners |= listener;
}
void InputHandler::onRenounce(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(!listener)return;
  listener->_handlers /= this;
  _listeners /= listener;
}

InputHandler::InputHandler() :  _mouseX(0), _mouseY(0), _mouseWheel(0){
  for(int i =0; i < MAX_MOUSE_BUTTONS; i++){
    _mouseButtonsDown[i]=0;
  }
  for(int i =0; i < MAX_KEYS; i++){
    _keysDown[i]=0;
  }
}

void InputHandler::onMouseMove(int x, int y){
  int dx = x - _mouseX;
  int dy = y - _mouseY;
  _mouseX = x;
  _mouseY = y;
  listeners().foreachElement([this,&dx,&dy](IInputListener * l){
    l->onMouseMove(_mouseX, _mouseY, dx,dy);
  });

}
void InputHandler::onMouseButtonDown(MouseButtons b){
  _mouseButtonsDown[b] = true;	
  listeners().foreachElement([this,&b](IInputListener * l){
    l->onMouseDown(b);
  });
}

bool InputHandler::accept(Object * object){
  return dynamic_cast<IInputListener*>(object)!=0;
}
void InputHandler::onMouseButtonUp(MouseButtons b){
  _mouseButtonsDown[b] = false;	

  listeners().foreachElement([this,&b](IInputListener * l){
    l->onMouseUp(b);
  });
}
void InputHandler::onKeyDown(Keys key){
  _keysDown[key] = true;	
  listeners().foreachElement([this,&key](IInputListener * l){
    l->onKeyDown(key);
  });
}
void InputHandler::onKeyUp(Keys key){
  _keysDown[key] = false;	
  listeners().foreachElement([this,&key](IInputListener * l){
    l->onKeyUp(key);
  });
}
void InputHandler::onMouseWheelMove(Real p){
  Real dp = p-_mouseWheel;
  _mouseWheel =p;
  listeners().foreachElement([this,&p,&dp](IInputListener * l){
    l->onMouseWheelMove(p,dp);
  });
}

bool InputHandler::isAnyKeyDown()const{
  for(int i=0; i <MAX_KEYS;i++ ){
    if(_keysDown[i])return true;
  }
  return false;
}
bool InputHandler::operator ()(MouseButtons button)const{
  return isMouseButtonDown(button);
}
bool InputHandler::operator()(Keys key)const{
  return isKeyDown(key);
}

bool InputHandler::isMouseButtonDown(MouseButtons b)const{
  return _mouseButtonsDown[b];
};
bool InputHandler::isKeyDown(Keys key)const{
  return _keysDown[key];
};

int InputHandler::mouseX()const{return _mouseX;}
int InputHandler::mouseY()const{return _mouseY;}
Real InputHandler::mouseWheel()const{return _mouseWheel;}
