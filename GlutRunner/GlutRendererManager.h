#pragma once
#include <Visualization/RenderEngine.h>
namespace IBDS{
class GlutRenderer : public RenderEngine{
public:
  static GlutRenderer & instance();
  bool initialize();
protected:
  void onSceneResized(int w, int h);
  GlutRenderer();
  ~GlutRenderer();
};

}