#pragma once
#include "CompositeRenderer.h"

#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Core/Timing/Timeable.h>

#include <Visualization/IRenderer.h>
#include <Visualization/Camera.h>

#include <functional>

namespace IBDS{
/**
 * \brief Render engine.
 *
 */
class RenderEngine:public SimulationModuleBase<IRenderer>,public virtual Timeable {
private:
  Camera * _camera;
  int _desiredFramerate;
public:  

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