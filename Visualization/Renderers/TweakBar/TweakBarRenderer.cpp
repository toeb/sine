#include "TweakBarRenderer.h"
#include <AntTweakBar/AntTweakBar.h>
#include <GL\glut.h>
#include <sstream>
#include <iostream>
#include <Visualization/UserInterface/RealValue.h>
using namespace IBDS;
using namespace std;

void TW_CALL setValueCallback(const void *value, void *clientData){
  IValue * callback = reinterpret_cast<IValue *>(clientData);
  callback->set(value);
}
void TW_CALL getValueCallback(void *value, void *clientData){
  IValue * callback = reinterpret_cast<IValue *>(clientData);
  callback->get(value);  
}

void TW_CALL actionCallback(void * clientdata){
  IAction * action = reinterpret_cast<IAction*>(clientdata);
  action->execute();
}


void TweakBarRenderer::addAction(IAction * action){
  //assert(action->getName());
  string name = *(action->getName());
  _actions[*(action->getName())]=action;
  stringstream ss;
  ss << " label='"<<name<<"' ";
  TwAddButton(_tweakBar,name.c_str(),actionCallback,action,ss.str().c_str());
}

void TweakBarRenderer::addValueCallback(IValue * callback){
  TwType type = TW_TYPE_UNDEF;
  if(dynamic_cast<IntValue*>(callback)){
    type = TW_TYPE_INT32;
  }
  if(dynamic_cast<RealValue*>(callback)){
    type = TW_TYPE_DOUBLE;
  }
  if(type == TW_TYPE_UNDEF)return;


  int r  =TwAddVarCB(
    _tweakBar,
    callback->getName()->c_str(), 
    type,
    setValueCallback,
    getValueCallback,
    callback,0);
}

void TweakBarRenderer::addComponent(IComponent * component){

}

bool TweakBarRenderer::addSimulationObject(ISimulationObject * object){
  processTweakBarEntries(object);
  return true;
}
void TweakBarRenderer::addEntry(ISimulationObject * o){
   auto action = dynamic_cast<IAction*>(o);
  if(action){
    addAction(action);
  }
  auto value = dynamic_cast<IValue *>(o);
  if(value){
    addValueCallback(value);
  }
}
bool TweakBarRenderer::removeSimulationObject(ISimulationObject * object){
  return false;
}
void TweakBarRenderer::processTweakBarEntries(ISimulationObject * object){
  _unprocessedObjects.push_back(object);
  if(!_initialized)return;

  for_each(_unprocessedObjects.begin(), _unprocessedObjects.end(), [this](ISimulationObject * o){
    this->addEntry(o);
  });
  _unprocessedObjects.clear();

}
void TweakBarRenderer::onKeyDown(Keys key){
  switch(key){
    case KEY_A:TwKeyPressed('a',0);break;

    case KEY_0:TwKeyPressed('0',0);break;
    case KEY_1:TwKeyPressed('1',0);break;
    case KEY_2:TwKeyPressed('2',0);break;
    case KEY_3:TwKeyPressed('3',0);break;
    case KEY_4:TwKeyPressed('4',0);break;
    case KEY_5:TwKeyPressed('5',0);break;
    case KEY_6:TwKeyPressed('6',0);break;
    case KEY_7:TwKeyPressed('7',0);break;
    case KEY_8:TwKeyPressed('8',0);break;
    case KEY_9:TwKeyPressed('9',0);break;
      
    case KEY_PERIOD:TwKeyPressed('.',0);break;
    case KEY_DELETE:TwKeyPressed(TW_KEY_DELETE,0);break;
    case KEY_BACKSPACE:TwKeyPressed(TW_KEY_BACKSPACE,0);break;
    case KEY_ENTER:TwKeyPressed(TW_KEY_RETURN,0);break;
  }
    //;//, TwMouseButton, TwMouseMotion, TwMouseWheel and TwWindowSiz
}
void TweakBarRenderer::onMouseMove(int x,int y, int dx, int dy){
  TwMouseMotion(x,y);
}
void TweakBarRenderer::onMouseDown(MouseButtons buttons){
  TwMouseButtonID b;
  switch(buttons){
    case BUTTON_LEFT:   b=TwMouseButtonID::TW_MOUSE_LEFT; break;
    case BUTTON_RIGHT:  b=TwMouseButtonID::TW_MOUSE_RIGHT; break;
    case BUTTON_MIDDLE: b=TwMouseButtonID::TW_MOUSE_MIDDLE; break;
    default: return;
  }
  TwMouseButton(TwMouseAction::TW_MOUSE_PRESSED,b);
}
void TweakBarRenderer::onMouseUp(MouseButtons buttons){
  TwMouseButtonID b;
  switch(buttons){
    case BUTTON_LEFT:   b=TwMouseButtonID::TW_MOUSE_LEFT; break;
    case BUTTON_RIGHT:  b=TwMouseButtonID::TW_MOUSE_RIGHT; break;
    case BUTTON_MIDDLE: b=TwMouseButtonID::TW_MOUSE_MIDDLE; break;
    default: return;
  }
  TwMouseButton(TwMouseAction::TW_MOUSE_RELEASED,b);
}
void TweakBarRenderer::sceneResized(int newWidth, int newHeight){
  TwWindowSize(newWidth,newHeight);
}
TweakBarRenderer::TweakBarRenderer():_initialized(false){

}
bool TweakBarRenderer::initializeObject(){
  if(!TwInit(TW_OPENGL,NULL))return false;
  
  if(!getName())setName("TweakBar");
  _tweakBar = TwNewBar(getName()->c_str());


  for(auto it = _actions.begin(); it != _actions.end(); it++){
    auto action = (*it).second;
    string name = *(action->getName());
    TwAddButton(_tweakBar,name.c_str(),actionCallback,action,0);
  }

  for_each(_values.begin(), _values.end(), [this](IValue * v){addValueCallback(v);});
  _initialized =true;
  return true;
}
void TweakBarRenderer::cleanupObject(){
  TwTerminate();
}

void TweakBarRenderer::render(){
  TwRefreshBar(_tweakBar);
  TwDraw(); 
}