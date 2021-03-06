#include "InputHandler.h"

#include <simulation.interaction/IInputListener.h>
using namespace nspace;

void InputHandler::itemAdded(IInputListener*,InputListeners){
  item->_handlers|=this;
}
void InputHandler::itemRemoved(IInputListener*,InputListeners){
  item->_handlers/=this;
}

void InputHandler::onAcception(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(!listener)return;
  InputListeners()|=listener;
}
void InputHandler::onRenounce(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(!listener)return;
  InputListeners()/=listener;
}

InputHandler::InputHandler() : _lastChange(0), _mouseX(0), _mouseY(0), _mouseWheel(0){
  setName("InputHandler");
  for(int i =0; i < MAX_MOUSE_BUTTONS; i++){
    _mouseButtonsDown[i]=0;
  }
  for(int i =0; i < MAX_KEYS; i++){
    _keysDown[i]=0;
  }
}

void InputHandler::onMouseMove(int x, int y){
  _lastChange = systemTime();
  int dx = x - _mouseX;
  int dy = y - _mouseY;
  _mouseX = x;
  _mouseY = y;
  InputListeners().foreachElement([this,&dx,&dy](IInputListener * l){
    l->onMouseMove(this,_mouseX, _mouseY, dx,dy);
  });
}
void InputHandler::onMouseButtonDown(MouseButtons b){
  _lastChange = systemTime();
  _mouseButtonsDown[b] = true;
  InputListeners().foreachElement([this,&b](IInputListener * l){
    l->onMouseDown(this,b);
  });
}

bool InputHandler::accept(Object * object){
  return dynamic_cast<IInputListener*>(object)!=0;
}
void InputHandler::onMouseButtonUp(MouseButtons b){
  _lastChange = systemTime();
  _mouseButtonsDown[b] = false;

  InputListeners().foreachElement([this,&b](IInputListener * l){
    l->onMouseUp(this,b);
  });
}
void InputHandler::onKeyDown(Keys key){
  _lastChange = systemTime();
  _keysDown[key] = true;
  InputListeners().foreachElement([this,&key](IInputListener * l){
    l->onKeyDown(this,key);
  });
}
void InputHandler::onKeyUp(Keys key){
  _lastChange = systemTime();
  _keysDown[key] = false;
  InputListeners().foreachElement([this,&key](IInputListener * l){
    l->onKeyUp(this,key);
  });
}
void InputHandler::onMouseWheelMove(Real p){
  _lastChange = systemTime();
  Real dp = p-_mouseWheel;
  _mouseWheel =p;
  InputListeners().foreachElement([this,&p,&dp](IInputListener * l){
    l->onMouseWheelMove(this,p,dp);
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