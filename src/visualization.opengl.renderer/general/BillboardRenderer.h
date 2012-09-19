#pragma once 
#include <common/Config.h>
#include <visualization/IRenderer.h>
#include <visualization.opengl/GlTexture.h>
namespace nspace{
  class BillboardRenderer : public IRenderer{
  private:
    Image * _image;
    Texture * _texture;
  public:
    void render();
    BillboardRenderer();
  protected:
    bool initializeRendering();
    bool initializeObject();
    void cleanupObject();
  };


}