#pragma once
#include <Visualization/IRenderer.h>
namespace IBDS{
  class CameraRenderer : public IRenderer{
  public:
    bool initialize();
  };
}
