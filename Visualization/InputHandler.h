#pragma once
#include <vector>
#include <algorithm>
#include <Simulation/ISimulationModule.h>
namespace IBDS{
  enum Keys{
    KEY_UNKNOWN,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SPACE,
    KEY_TAB,
    KEY_ENTER,
    KEY_F1       ,
    KEY_F2       ,
    KEY_F3       ,
    KEY_F4       ,
    KEY_F5       ,
    KEY_F6       ,
    KEY_F7       ,
    KEY_F8       ,
    KEY_F9       ,
    KEY_F10      ,
    KEY_F11      ,
    KEY_F12      ,
    KEY_LEFT     ,
    KEY_UP       ,
    KEY_RIGHT    ,
    KEY_DOWN     ,
    KEY_PAGE_UP  ,
    KEY_PAGE_DOWN,
    KEY_HOME     ,
    KEY_END      ,
    KEY_INSERT   ,
    KEY_NUM_LOCK ,
    KEY_BEGIN    ,
    KEY_DELETE   ,
    KEY_CTRL,
    KEY_ALT,
    KEY_SHIFT
  };
  enum MouseButtons{
    BUTTON_UNKNOWN=99,
    BUTTON_LEFT=0,
    BUTTON_RIGHT=1,
    BUTTON_MIDDLE=2
  };
  class InputHandler;
  class IInputListener{
  public:
    virtual void setInputHandler(InputHandler * handler){};
    virtual void onKeyDown(Keys key){};
    virtual void onKeyUp(Keys key){};
    
    virtual void onMouseDown(MouseButtons button){};
    virtual void onMouseUp(MouseButtons button){};
        
    virtual void onMouseMove(int x, int y, int dx, int dy){};
    virtual void onMouseWheelMove(int amount){};

  };

#define MAX_KEYS 256
#define MAX_MOUSE_BUTTONS 3
class InputHandler:public ISimulationModule{
  private:
    std::vector<IInputListener*> _listeners;
    bool _keysDown[MAX_KEYS];
    bool _mouseButtonsDown[MAX_MOUSE_BUTTONS];
    int _mouseX;
    int _mouseY;
    int _mouseLastX;
    int _mouseLastY;
    int _mouseDX;
    int _mouseDY;
    int _mouseWheel;
    int _mouseWheelLast;
    int _mouseWheelDelta;
  public:
    bool addSimulationObject(ISimulationObject * object){
      if(dynamic_cast<InputHandler*>(object))return false;
      IInputListener * listener = dynamic_cast<IInputListener*>(object);
      if(!listener)return false;
      addInputListener(listener);
    }
    void reset(){
      _listeners.clear();
    }
    void addInputListener(IInputListener * listener){
      _listeners.push_back(listener);
    }
    InputHandler(){
      for(int i=0; i< MAX_KEYS;i++){
        _keysDown[i]=false;
      }
      for(int i=0; i < MAX_MOUSE_BUTTONS;i++){
        _mouseButtonsDown[i]=false;
      }
    }
    void onMouseMove(int x, int y, int dx, int dy){
      for(auto l = _listeners.begin(); l != _listeners.end(); l++){
        (*l)->onMouseMove(x,y,dx,dy);
      }
    }

    bool isKeyDown(Keys key){return _keysDown[key];};
    int getMouseX(){return 0;}
    int getMouseY(){return 0;}
    int getMouseDeltaX(){return 0;}
    int getMouseDeltaY(){return 0;}
    bool isAnyKeyDown(){
      for(int i=0; i < MAX_KEYS; i++){
        if(_keysDown[i])return true;
      }
    }
    void setMouseWheelPosition(int p){};
    void setMousePosition(int x, int y){};
    void onKeyDown(Keys key){
      _keysDown[key]=true;    
      for(auto l = _listeners.begin(); l != _listeners.end(); l++){
        (*l)->onKeyDown(key);
      }
    };
    void onKeyUp(Keys key){
      _keysDown[key]=false;
      for(auto l = _listeners.begin(); l != _listeners.end(); l++){
        (*l)->onKeyUp(key);
      }
    };
    void onMouseDown(MouseButtons button){
      _mouseButtonsDown[button]=true;    
      for(auto l = _listeners.begin(); l != _listeners.end(); l++){
        (*l)->onMouseDown(button);
      }
    }
    void onMouseUp(MouseButtons button){
      _mouseButtonsDown[button]=false;
      for(auto l = _listeners.begin(); l != _listeners.end(); l++){
        (*l)->onMouseUp(button);
      }
    }
  };
}