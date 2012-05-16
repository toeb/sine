#include "GlutInputHandler.h"
#include <Visualization/MiniGL.h>
#include <freeglut/include/GL/glut.h>
#include <freeglut/include/GL/freeglut_ext.h>
#include <iostream>
#include <Common/timing.h>
using namespace IBDS;
using namespace std;

GlutInputHandler * _glutInputHandlerInstance=0;
GlutInputHandler & GlutInputHandler::instance(){
  if(!_glutInputHandlerInstance)_glutInputHandlerInstance=new GlutInputHandler();
  return *_glutInputHandlerInstance;
}

GlutInputHandler::GlutInputHandler(){}
GlutInputHandler::~GlutInputHandler(){}
Keys charToKeyCode(char c){
   c = toupper(c);
  switch(c){
  case 'A': return Keys::KEY_A; break;
  case 'B': return Keys::KEY_B; break;
  case 'C': return Keys::KEY_C; break;
  case 'D': return Keys::KEY_D; break;
  case 'E': return Keys::KEY_E; break;
  case 'F': return Keys::KEY_F; break;
  case 'G': return Keys::KEY_G; break;
  case 'H': return Keys::KEY_H; break;
  case 'I': return Keys::KEY_I; break;
  case 'J': return Keys::KEY_J; break;
  case 'K': return Keys::KEY_K; break;
  case 'L': return Keys::KEY_L; break;
  case 'M': return Keys::KEY_M; break;
  case 'N': return Keys::KEY_N; break;
  case 'O': return Keys::KEY_O; break;
  case 'P': return Keys::KEY_P; break;
  case 'Q': return Keys::KEY_Q; break;
  case 'R': return Keys::KEY_R; break;
  case 'S': return Keys::KEY_S; break;
  case 'T': return Keys::KEY_T; break;
  case 'U': return Keys::KEY_U; break;
  case 'V': return Keys::KEY_V; break;
  case 'W': return Keys::KEY_W; break;
  case 'X': return Keys::KEY_X; break;
  case 'Y': return Keys::KEY_Y; break;
  case 'Z': return Keys::KEY_Z; break;
  case '0': return Keys::KEY_0; break;
  case '1': return Keys::KEY_1; break;
  case '2': return Keys::KEY_2; break;
  case '3': return Keys::KEY_3; break;
  case '4': return Keys::KEY_4; break;
  case '5': return Keys::KEY_5; break;
  case '6': return Keys::KEY_6; break;
  case '7': return Keys::KEY_7; break;
  case '8': return Keys::KEY_8; break;
  case '9': return Keys::KEY_9; break;
  case '\n':return Keys::KEY_ENTER; break;
  case ' ':return Keys::KEY_SPACE;break;
  case '\t':return Keys::KEY_TAB;break;

  default:
    return Keys::KEY_UNKNOWN;
  }
}

Keys glutSpecialKeyToKeys(int key){  switch(key){
   case GLUT_KEY_F1            : return      Keys::KEY_F1          ;
   case GLUT_KEY_F2            : return      Keys::KEY_F2          ;
   case GLUT_KEY_F3            : return      Keys::KEY_F3          ;
   case GLUT_KEY_F4            : return      Keys::KEY_F4          ;
   case GLUT_KEY_F5            : return      Keys::KEY_F5          ;
   case GLUT_KEY_F6            : return      Keys::KEY_F6          ;
   case GLUT_KEY_F7            : return      Keys::KEY_F7          ;
   case GLUT_KEY_F8            : return      Keys::KEY_F8          ;
   case GLUT_KEY_F9            : return      Keys::KEY_F9          ;
   case GLUT_KEY_F10           : return      Keys::KEY_F10         ;
   case GLUT_KEY_F11           : return      Keys::KEY_F11         ;
   case GLUT_KEY_F12           : return      Keys::KEY_F12         ;
   case GLUT_KEY_LEFT          : return      Keys::KEY_LEFT        ;
   case GLUT_KEY_UP            : return      Keys::KEY_UP          ;
   case GLUT_KEY_RIGHT         : return      Keys::KEY_RIGHT       ;
   case GLUT_KEY_DOWN          : return      Keys::KEY_DOWN        ;
   case GLUT_KEY_PAGE_UP       : return      Keys::KEY_PAGE_UP     ;
   case GLUT_KEY_PAGE_DOWN     : return      Keys::KEY_PAGE_DOWN   ;
   case GLUT_KEY_HOME          : return      Keys::KEY_HOME        ;
   case GLUT_KEY_END           : return      Keys::KEY_END         ;
   case GLUT_KEY_INSERT        : return      Keys::KEY_INSERT      ;
   case GLUT_KEY_NUM_LOCK      : return      Keys::KEY_NUM_LOCK    ;
   case GLUT_KEY_BEGIN         : return      Keys::KEY_BEGIN       ;
   case GLUT_KEY_DELETE        : return      Keys::KEY_DELETE      ;
  }
}
void modifierDown(){
  int modifier = glutGetModifiers();
  GlutInputHandler & instance = GlutInputHandler::instance();

  if(modifier & GLUT_ACTIVE_CTRL) instance.onKeyDown(Keys::KEY_CTRL);
  if(modifier & GLUT_ACTIVE_ALT) instance.onKeyDown(Keys::KEY_ALT);
  if(modifier & GLUT_ACTIVE_SHIFT) instance.onKeyDown(Keys::KEY_SHIFT);
}
void modifierUp(){  
  int modifier = glutGetModifiers();
  GlutInputHandler & instance = GlutInputHandler::instance();
  if(instance.isAnyKeyDown())return;
  if(modifier & GLUT_ACTIVE_CTRL) instance.onKeyUp(Keys::KEY_CTRL);
  if(modifier & GLUT_ACTIVE_ALT) instance.onKeyUp(Keys::KEY_ALT);
  if(modifier & GLUT_ACTIVE_SHIFT) instance.onKeyUp(Keys::KEY_SHIFT);
}

void keyDown(unsigned char c, int x, int y){
  
  GlutInputHandler::instance().onKeyDown(charToKeyCode(c));
  modifierDown();
}
void keyUp(unsigned char c, int x, int y){
  GlutInputHandler::instance().onKeyUp(charToKeyCode(c));
  modifierUp();
}
void specialUp(int key,int x, int y){
  GlutInputHandler::instance().onKeyUp(glutSpecialKeyToKeys(key));
  modifierUp();
}
void specialDown(int key,int x, int y){
  GlutInputHandler::instance().onKeyDown(glutSpecialKeyToKeys(key));
  modifierDown();
}
void mouseWheel(int btn, int dir, int x, int y){
}

void mousePress(int btn, int state, int x, int y){
  MouseButtons button;
  switch(btn){
    case GLUT_LEFT_BUTTON: button=MouseButtons::BUTTON_LEFT;break;
    case GLUT_RIGHT_BUTTON: button=MouseButtons::BUTTON_RIGHT;break;
    case GLUT_MIDDLE_BUTTON: button=MouseButtons::BUTTON_MIDDLE;break;
  default:
    button = MouseButtons::BUTTON_UNKNOWN;
    return;
  }
 switch(state){
 case GLUT_DOWN:
   GlutInputHandler::instance().onMouseDown(button);
   modifierDown();
   break;
 case GLUT_UP:
   GlutInputHandler::instance().onMouseUp(button);
  modifierUp();
   break;
 default:
   break;
 }
  
}
int lastX,lastY;
bool firstStep=true;
void mouseMove(int x, int y){
  if(firstStep){
    lastX = x;
    lastY = y;
    firstStep =false;
  }
  GlutInputHandler::instance().onMouseMove(x,y,x-lastX,y-lastY);
  lastX = x;
  lastY = y;
}

bool GlutInputHandler::initializeObject(){
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);  
	glutMouseWheelFunc(mouseWheel);  
	glutMouseFunc (mousePress);  
	glutMotionFunc (mouseMove);
	glutSpecialFunc (specialDown);
  glutSpecialUpFunc(specialUp);
  glutPassiveMotionFunc(mouseMove);
  return true;
}