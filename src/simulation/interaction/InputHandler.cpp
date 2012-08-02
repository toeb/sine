#include "InputHandler.h"

#include <simulation/interaction/IInputListener.h>
using namespace nspace;
InputHandler::InputHandler() :  _mouseX(0), _mouseY(0), _mouseWheel(0){
  setName("InputHandler");
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
	foreachObject([this,&dx,&dy](IInputListener * l){
		l->onMouseMove(_mouseX, _mouseY, dx,dy);
	});

}
void InputHandler::onMouseButtonDown(MouseButtons b){
	_mouseButtonsDown[b] = true;	
	foreachObject([this,&b](IInputListener * l){
		l->onMouseDown(b);
	});
}
void InputHandler::onMouseButtonUp(MouseButtons b){
	_mouseButtonsDown[b] = false;	
		foreachObject([this,&b](IInputListener * l){
			l->onMouseUp(b);
	});
}
void InputHandler::onKeyDown(Keys key){
	_keysDown[key] = true;	
	foreachObject([this,&key](IInputListener * l){
			l->onKeyDown(key);
	});
}
void InputHandler::onKeyUp(Keys key){
	_keysDown[key] = false;	
	foreachObject([this,&key](IInputListener * l){
			l->onKeyUp(key);
	});
}
void InputHandler::onMouseWheelMove(Real p){
	Real dp = p-_mouseWheel;
	_mouseWheel =p;
		foreachObject([this,&p,&dp](IInputListener * l){
			l->onMouseWheelMove(p,dp);
	});
}

