#pragma once
#include <visualization/core/RenderModule.h>
namespace nspace{
class GlutRenderer : public RenderModule{
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