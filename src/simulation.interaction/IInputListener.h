#pragma once
#include <core/Object.h>
#include <core/Set.h>
#include <simulation.interaction/Keys.h>
namespace nspace{
  class InputHandler;
  class IInputListener : public virtual Object{ 
    TYPED_OBJECT(IInputListener);
  private:
    Set<InputHandler*> _handlers;
    friend class InputHandler;
  public:
    const Set<InputHandler*> handlers()const{return _handlers;}   

    virtual void onKeyDown(InputHandler * sender, Keys key){onKeyDown(key);};    
    virtual void onKeyDown(Keys key){};
    virtual void onKeyUp(InputHandler * sender, Keys key){onKeyUp(key);};    
    virtual void onKeyUp(Keys key){};
    
    virtual void onMouseDown(InputHandler * sender, MouseButtons button){onMouseDown(button);};  
    virtual void onMouseDown(MouseButtons button){};
    virtual void onMouseUp(InputHandler * sender, MouseButtons button){onMouseUp(button);};  
    virtual void onMouseUp(MouseButtons button){};

    virtual void onMouseMove(InputHandler * sender, int x, int y, int dx, int dy){onMouseMove(x, y, dx, dy);};  
    virtual void onMouseMove(int x, int y, int dx, int dy){};
    virtual void onMouseWheelMove(InputHandler * sender, Real p, Real dp){};
    virtual void onMouseWheelMove(Real p, Real dp){};
  };


  class DelegateKeyListener : public virtual IInputListener{
    TYPED_OBJECT(DelegateKeyListener);
  public:
    enum KeyState{
      Down,Up
    };
  private:
    std::function<void (Keys,KeyState)> _callback;
  public:
    DelegateKeyListener(std::function<void (Keys,KeyState)> callback):_callback(callback){
    }
    void onKeyDown(Keys key){_callback(key,Down);};
    void onKeyUp(Keys key){_callback(key,Up);};
  };
}