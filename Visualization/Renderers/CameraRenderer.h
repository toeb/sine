#pragma once
#include <Visualization/IRenderer.h>
#include <Visualization/InputHandler.h>
#include <Simulation/Kinematics/KinematicBody.h>
#include <Visualization/RenderEngine.h>
namespace IBDS{

class CameraRenderer : 
  public Camera,
  public IRenderer,
  public IInputListener,
  public KinematicBody
{
private:
  InputHandler * _input;
public:    
  void setInputHandler(InputHandler * handler);
  void onBeforeRenderering();
  void onMouseMove(int x, int y, int dx, int dy);
  void camera();
};  
}
