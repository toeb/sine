#include "GlutInputHandler.h"
#include <visualization.opengl/MiniGL.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
using namespace nspace;
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
  case 'A':   return KEY_A; break;
  case 'B':   return KEY_B; break;
  case 'C':   return KEY_C; break;
  case 'D':   return KEY_D; break;
  case 'E':   return KEY_E; break;
  case 'F':   return KEY_F; break;
  case 'G':   return KEY_G; break;
  case 'H':   return KEY_H; break;
  case 'I':   return KEY_I; break;
  case 'J':   return KEY_J; break;
  case 'K':   return KEY_K; break;
  case 'L':   return KEY_L; break;
  case 'M':   return KEY_M; break;
  case 'N':   return KEY_N; break;
  case 'O':   return KEY_O; break;
  case 'P':   return KEY_P; break;
  case 'Q':   return KEY_Q; break;
  case 'R':   return KEY_R; break;
  case 'S':   return KEY_S; break;
  case 'T':   return KEY_T; break;
  case 'U':   return KEY_U; break;
  case 'V':   return KEY_V; break;
  case 'W':   return KEY_W; break;
  case 'X':   return KEY_X; break;
  case 'Y':   return KEY_Y; break;
  case 'Z':   return KEY_Z; break;
  case '0':   return KEY_0; break;
  case '1':   return KEY_1; break;
  case '2':   return KEY_2; break;
  case '3':   return KEY_3; break;
  case '4':   return KEY_4; break;
  case '5':   return KEY_5; break;
  case '6':   return KEY_6; break;
  case '7':   return KEY_7; break;
  case '8':   return KEY_8; break;
  case '9':   return KEY_9; break;
  case '\n':  return KEY_ENTER; break;
  case ' ':   return KEY_SPACE;break;
  case '\t':  return KEY_TAB;break;
  case '\b':  return KEY_BACKSPACE;break;
  case '.':   return KEY_PERIOD;break;

  default:
    return KEY_UNKNOWN;
  }
}

Keys glutSpecialKeyToKeys(int key){  switch(key){
case GLUT_KEY_F1            : return      KEY_F1          ;
case GLUT_KEY_F2            : return      KEY_F2          ;
case GLUT_KEY_F3            : return      KEY_F3          ;
case GLUT_KEY_F4            : return      KEY_F4          ;
case GLUT_KEY_F5            : return      KEY_F5          ;
case GLUT_KEY_F6            : return      KEY_F6          ;
case GLUT_KEY_F7            : return      KEY_F7          ;
case GLUT_KEY_F8            : return      KEY_F8          ;
case GLUT_KEY_F9            : return      KEY_F9          ;
case GLUT_KEY_F10           : return      KEY_F10         ;
case GLUT_KEY_F11           : return      KEY_F11         ;
case GLUT_KEY_F12           : return      KEY_F12         ;
case GLUT_KEY_LEFT          : return      KEY_LEFT        ;
case GLUT_KEY_UP            : return      KEY_UP          ;
case GLUT_KEY_RIGHT         : return      KEY_RIGHT       ;
case GLUT_KEY_DOWN          : return      KEY_DOWN        ;
case GLUT_KEY_PAGE_UP       : return      KEY_PAGE_UP     ;
case GLUT_KEY_PAGE_DOWN     : return      KEY_PAGE_DOWN   ;
case GLUT_KEY_HOME          : return      KEY_HOME        ;
case GLUT_KEY_END           : return      KEY_END         ;
case GLUT_KEY_INSERT        : return      KEY_INSERT      ;
case GLUT_KEY_NUM_LOCK      : return      KEY_NUM_LOCK    ;
case GLUT_KEY_BEGIN         : return      KEY_BEGIN       ;
case GLUT_KEY_DELETE        : return      KEY_DELETE      ;
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
void mouseWheelFunc(int btn, int dir, int x, int y){
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
   GlutInputHandler::instance().onMouseButtonDown(button);
   modifierDown();
   break;
 case GLUT_UP:
   GlutInputHandler::instance().onMouseButtonUp(button);
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
  GlutInputHandler::instance().onMouseMove(x,y);
  lastX = x;
  lastY = y;
}

bool GlutInputHandler::initializeObject(){
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);  
	glutMouseWheelFunc(mouseWheelFunc);  
	glutMouseFunc (mousePress);  
	glutMotionFunc (mouseMove);
	glutSpecialFunc (specialDown);
  glutSpecialUpFunc(specialUp);
  glutPassiveMotionFunc(mouseMove);
  return true;
}