#include "TweakBarRenderer.h"
#include <AntTweakBar/AntTweakBar.h>
#include <GL\glut.h>

#include <iostream>
using namespace IBDS;

void TweakBarRenderer::onKeyDown(Keys key){
  switch(key){
    case KEY_A:TwKeyPressed('a',0);break;
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

bool TweakBarRenderer::initialize(){
  if(!TwInit(TW_OPENGL,NULL))return false;
  
  if(!getName())setName("TweakBar");
  _tweakBar = TwNewBar(getName()->c_str());

  // send the ''glutGetModifers'' function pointer to AntTweakBar
  //TwGLUTModifiersFunc(glutGetModifiers);
  //_tweakBar = TwNewBar("TweakBar");
  // 	// turn wireframe mode on
  //int val = 1;
  //setWireframeCB(&val,NULL);

  // Create a tweak bar
/*	_tweakBar = TwNewBar("TweakBar");
  TwDefine(" GLOBAL help='TweakBarRenderer TweakBar.' "); // Message added to the help bar.
  TwDefine(" TweakBar size='250 250' position='5 5' color='96 200 224' text=dark "); // change default tweak bar size and color
  /*
  TwAddVarRO(m_tweakBar, "Time", TW_TYPE_FLOAT, &m_time, " label='Time' precision=5");

  TwAddVarCB(m_tweakBar, "Rotation", TW_TYPE_QUAT4F, setRotationCB, getRotationCB, &m_quat, 
    " label='Rotation' open help='Change the rotation.' ");

  // Add callback to toggle auto-rotate mode (callback functions are defined above).
  TwAddVarCB(m_tweakBar, "Wireframe", TW_TYPE_BOOL32, setWireframeCB, getWireframeCB, NULL, 
    " label='Wireframe' key=w help='Toggle wireframe mode.' ");
    */
  return true;
}
void TweakBarRenderer::cleanup(){
  TwTerminate();
}

void TweakBarRenderer::render(){
  TwRefreshBar(_tweakBar);
  TwDraw(); 
}