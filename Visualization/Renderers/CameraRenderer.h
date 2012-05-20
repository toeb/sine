#pragma once
#include <Visualization/IRenderer.h>
#include <Visualization/InputHandler.h>
#include <Simulation/Integrators/IIntegrable.h>
#include <Simulation/Kinematics/KinematicBody.h>
namespace IBDS{

class CameraRenderer : public IRenderer,public IInputListener/*,public KinematicBody*/{
  private:
    InputHandler * _input;
  public:    
    void setInputHandler(InputHandler * handler);
    void render();
    void onBeforeRenderering();
  };

  
}
