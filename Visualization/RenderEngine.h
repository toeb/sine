#pragma once
#include "IRenderer.h"
#include "CompositeRenderer.h"
#include <Simulation/ISimulationObject.h>
#include "RenderManager.h"
namespace IBDS{

/**
 * \brief Render engine.
 *
 */
class RenderEngine:public ISimulationObject{
private:
  CompositeRenderer * _renderers;
  RenderManager * _renderManager;
  int _desiredFramerate;
public:
  void setRenderManager(RenderManager* renderMan);
  RenderManager * getRenderManager();
  void setDesiredFramerate(int hz);
  int getDesiredFramerate()const;

  /**
   * \brief Runs this object.
   * 				
   * 				must call render
   * 				must call initialize 
   * 				must call cleanup
   */
  virtual void run()=0;
  void render();
  bool initialize();
  void cleanup();
  RenderEngine();
  ~RenderEngine();
  CompositeRenderer & getRenderers();
protected:
  virtual void onDesiredFramerateChanged(){};
  virtual void onBeforeRender(){};
  virtual void onAfterRender(){};
};
}