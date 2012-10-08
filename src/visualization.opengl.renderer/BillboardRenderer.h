#pragma once 
#include <config.h>
#include <visualization/Renderer.h>
#include <visualization.opengl/GlTexture.h>
namespace nspace{
  class BillboardRenderer : public Renderer{
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