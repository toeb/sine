#pragma once
#include "IRenderer.h"
#include "CompositeRenderer.h"
#include <Simulation/ISimulationObject.h>

#include <Simulation/ISimulationModule.h>
namespace IBDS{
  class Camera : virtual public ISimulationObject{
    virtual void camera()=0;

  };
/**
 * \brief Render engine.
 *
 */
class RenderEngine:public ISimulationModule{
private:
  Camera * camera;
  CompositeRenderer _renderers;
  int _desiredFramerate;
public:
  bool addSimulationObject(ISimulationObject * object);
  void reset();
    
  void setDesiredFramerate(int hz);
  int getDesiredFramerate()const;
  int getSceneWidth(){return 800;}
  int getSceneHeight(){return 600;}
    
  void render();

  
  RenderEngine();
  ~RenderEngine();
  
  CompositeRenderer & getRenderers();
protected:
  virtual bool initializeRenderEngine()=0;
  bool initializeObject();
  void cleanupObject();
  virtual void cleanupRenderEngine()=0;
  void resizeScene(int newWidth, int newHeight);
  virtual void onSceneResized(int newWidth,int newHeight){};
  virtual void onDesiredFramerateChanged(){};
  virtual void onBeforeRender(){};
  virtual void onAfterRender(){};
};
}