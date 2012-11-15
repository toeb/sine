#pragma once
#include <vector>
#include <map>
#include <algorithm>

#include <simulation.interaction/Keys.h>
#include <math/core.h>
#include <simulation.interaction/IInputListener.h>
#include <core.hub/ModuleBase.h>
#include <core.h>
#include <core.logging/Log.h>
namespace nspace{
  //an inputhandler is a module which translates input into events for IInputListeners and keeps track of keyboard / mouse input state
  class InputHandler:public virtual ModuleBase,public virtual NamedObject, public virtual Log{
    REFLECTABLE_OBJECT(InputHandler);
    PROPERTYSET(IInputListener*, InputListeners,,);
  private:
    // store the last change time which allows clients to see which is the current inputhandler
    Time _lastChange;
    // the array of keys which are currently pressed
    bool _keysDown[MAX_KEYS];
    // the array of mouse buttons which are currently pressed
    bool _mouseButtonsDown[MAX_MOUSE_BUTTONS];
    // the mouse position of this inputhander
    int _mouseX;
    int _mouseY;
    // the mouse wheel position of this inputhandler
    Real _mouseWheel;
  public:    
    Time lastChange()const{return _lastChange;}
    // override of ModuleBase.  this module only accepts iinputlistener objects
    bool accept(Object * object);
    //default constructor
    InputHandler();
    // returns true if any key is currently being pressed
    bool isAnyKeyDown()const;
    // returns true if the button specified is currently beeing pressend
    bool operator ()(MouseButtons button)const;
    // returns true if the key specified is currently being pressend
    bool operator()(Keys key)const;
    // returns true if the mouse button specified is being pressed
    virtual bool isMouseButtonDown(MouseButtons b)const;
    // returns brief key is being pressed
    virtual bool isKeyDown(Keys key)const;
    // returns the mouse x position
    virtual int mouseX()const;
    // retunrs the mouse y position
    virtual int mouseY()const;
    // returns the mouse wheel value
    virtual Real mouseWheel()const;

    //
    void onMouseMove(int x, int y);
    void onMouseButtonDown(MouseButtons b);
    void onKeyDown(Keys key);
    void onKeyUp(Keys key);
    void onMouseButtonUp(MouseButtons b);
    void onMouseWheelMove(Real p);
  protected:
    void onAcception(Object * object);
    void onRenounce(Object * object);
  };


}