#pragma once

#include <simulation/SimulationModuleBase.h>
#include <simulation.timing/Timeable.h>

#include <visualization/IRenderer.h>
#include <visualization/Viewport.h>

#include <simulation.logging/LoggingObject.h>

#include <functional>

namespace nspace{
/**
 * \brief Render Module.
 *
 */
class RenderModule:public virtual SimulationModuleBase<IRenderer>,public virtual Timeable, public virtual LoggingObject {
private:
  bool _renderingInitialized;
  Viewport * _viewport;
  int _desiredFramerate;
  int _sceneWidth;
  int _sceneHeight;
public:  
  void setDesiredFramerate(int hz);
  int getDesiredFramerate()const;

  int getSceneWidth(){return _sceneWidth;}
  int getSceneHeight(){return _sceneHeight;}
    
  void render();

  RenderModule();
  ~RenderModule();

	void setViewport(Viewport * viewport);
  Viewport * viewport(){
    return _viewport;
  }
protected:
  void initializeRendering();
  bool initializeObject();
  void cleanupObject();
  void onPotentialSimulationObjectAdd(ISimulationObject * object);

  void resizeScene(int newWidth, int newHeight);
  
  virtual bool initializeRenderEngine()=0;
  virtual void cleanupRenderEngine()=0;

  virtual void onSceneResized(int newWidth,int newHeight){};
  virtual void onDesiredFramerateChanged(){};
  virtual void onBeforeRender(){};
  virtual void onAfterRender(){};
};
}