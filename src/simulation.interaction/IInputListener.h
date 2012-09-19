#pragma once
#include <simulation.interaction/Keys.h>

#include <simulation/ISimulationObject.h>
namespace nspace{
  class InputHandler;
  class IInputListener : public virtual ISimulationObject{ 
  public:
    virtual void setInputHandler(InputHandler * handler){};
    virtual void onKeyDown(Keys key){};
    virtual void onKeyUp(Keys key){};
    
    virtual void onMouseDown(MouseButtons button){};
    virtual void onMouseUp(MouseButtons button){};
        
    virtual void onMouseMove(int x, int y, int dx, int dy){};
    virtual void onMouseWheelMove(Real p, Real dp){};
  };
}