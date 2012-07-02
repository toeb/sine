#pragma once
#include "IRenderer.h"
#include "CompositeRenderer.h"
#include <Simulation/Core/ISimulationObject.h>

#include <Simulation/Core/SimulationModuleBase.h>
#include <functional>

namespace IBDS{
class Camera : virtual public ISimulationObject{
public:
  virtual void camera()=0;
};



/**
 * \brief Render engine.
 *
 */
class RenderEngine:public SimulationModuleBase<IRenderer>{
private:
  Camera * _camera;
  int _desiredFramerate;
public:  
  void reset();
    
  void setDesiredFramerate(int hz);
  int getDesiredFramerate()const;
  int getSceneWidth(){return 800;}
  int getSceneHeight(){return 600;}
    
  void render();

  RenderEngine();
  ~RenderEngine();
  
protected:
  bool initializeObject();
  void cleanupObject();
  
  void onBeforeSimulationObjectAdd(ISimulationObject * object);

  void resizeScene(int newWidth, int newHeight);
  
  virtual bool initializeRenderEngine()=0;
  virtual void cleanupRenderEngine()=0;

  virtual void onSceneResized(int newWidth,int newHeight){};
  virtual void onDesiredFramerateChanged(){};
  virtual void onBeforeRender(){};
  virtual void onAfterRender(){};
};
}