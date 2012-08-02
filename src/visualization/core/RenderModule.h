#pragma once

#include <simulation/core/SimulationModuleBase.h>
#include <simulation/timing/Timeable.h>

#include <visualization/core/IRenderer.h>
#include <visualization/core/Viewport.h>

#include <functional>

namespace nspace{
/**
 * \brief Render Module.
 *
 */
class RenderModule:public virtual SimulationModuleBase<IRenderer>,public virtual Timeable {
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
