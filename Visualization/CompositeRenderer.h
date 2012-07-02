#pragma once
#include "IRenderer.h"
#include <vector>
namespace IBDS{
class CompositeRenderer:public IRenderer{
private:
  std::vector<IRenderer*> _renderers;
public:
  CompositeRenderer();
  ~CompositeRenderer();
  const std::vector<IRenderer*>& getRenderers()const;
  void removeRenderer(IRenderer * renderer);
  void addRenderer(IRenderer * renderer);
  void clearRenderers();
  void render();
  void onBeforeRenderering();
  void sceneResized(int newWIdth, int newHeight);
protected:  
  bool initializeObject();
  void cleanupObject();
};
}