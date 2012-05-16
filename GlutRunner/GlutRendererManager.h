#pragma once
#include <Visualization/RenderEngine.h>
namespace IBDS{
class GlutRenderer : public RenderEngine{
public:
  static GlutRenderer & instance();
protected:
  bool initializeRenderEngine();
  void cleanupRenderEngine();
  void onSceneResized(int w, int h);
  GlutRenderer();
  ~GlutRenderer();
};

}