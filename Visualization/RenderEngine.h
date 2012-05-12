#pragma once
#include "IRenderer.h"
#include "CompositeRenderer.h"
#include <Simulation/ISimulationObject.h>

#include <Simulation/ISimulationAlgorithm.h>
namespace IBDS{

/**
 * \brief Render engine.
 *
 */
class RenderEngine:public ISimulationAlgorithm{
private:
  CompositeRenderer _renderers;
  int _desiredFramerate;
public:
  bool addSimulationObject(ISimulationObject * object);
  void reset();
    
  void setDesiredFramerate(int hz);
  int getDesiredFramerate()const;
    
  void render();
  bool initialize();
  void cleanup();
  
  RenderEngine();
  ~RenderEngine();
  
  CompositeRenderer & getRenderers();
protected:
  void resizeScene(int newWidth, int newHeight);
  virtual void onSceneResized(int newWidth,int newHeight){};
  virtual void onDesiredFramerateChanged(){};
  virtual void onBeforeRender(){};
  virtual void onAfterRender(){};
};
}